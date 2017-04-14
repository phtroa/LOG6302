#include <vector>
#include <memory>
#include <set>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <clang/Tooling/Tooling.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/CompilerInstance.h>

#include "BackwardSlicer.h"
#include "CFGVisitor.h"
#include "CDGraphBuilder.h"
#include "DDGraphBuilder.h"
#include "Dominator.h"
#include "ForwardSlicer.h"
#include "MetaTree.h"
#include "MetricASTVisitor.h"
#include "MergeGraph.h"
#include "PostDominator.h"
#include "PrettyPrintASTVisitor.h"
#include "ReachingDef.h"
#include "UMLASTVisitor.h"
#include "Visitor.h"

static unsigned int current_file = 0;
static size_t nb_files = 0;
static std::shared_ptr<ASTTree> myAst;
static std::shared_ptr<MetaTree> infoTree;

void print_usage() {
    std::cout << "Usage: --input file --ast file --metric file" << std::endl;
    std::cout << "--uml file --cfg file --dom file --pdom file" << std::endl;
    std::cout << "--rea file --cdGraph file --ddGraph file --pdg file" << std::endl;
    std::cout << "--fSlice file --bSlice file --line n --varName name" << std::endl;
}

/******************************************************************************/
/* MyASTConsumer                                                              */
/******************************************************************************/
class MyASTConsumer : public clang::ASTConsumer {
 public:

  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
    //We build an unique tree that is updated each time a new file is visited
    Visitor visitor(Context, myAst, infoTree);
    visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }
};

/******************************************************************************/
/* MyFrontendAction                                                           */
/******************************************************************************/
class MyFrontendAction : public clang::ASTFrontendAction {
 public:
  clang::ASTConsumer* CreateASTConsumer(clang::CompilerInstance &CI,
                                                        llvm::StringRef file) override {
    current_file++;
    double pourc = current_file * 100.0 / nb_files;
    std::cout << "[" << std::to_string((int) std::round(pourc)) << "%] " << file.str() << std::endl;

    return new MyASTConsumer; // Takes ownership of the pointer
  }
};

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/
int main(int argc, char **argv) {

  if (argc <= 1) {
    print_usage();
    return 0;
  }

  //file names
  std::string input;
  std::string ast_file;
  std::string metric_file;
  std::string uml_file;
  std::string cfg_file;
  std::string dom_file;
  std::string pdom_file;
  std::string rea_file;
  std::string cdG_file;
  std::string ddG_file;
  std::string pdG_file;
  std::string fSlice_file;
  std::string bSlice_file;

  std::set<std::string> isRequired;
  int lineForSlice = -1;
  std::string varNameForSlice;
  bool mustComputeCFG = false;

  //Initialisation de l'arbre
  myAst = std::shared_ptr<ASTTree>(new ASTTree());
  myAst->setRoot(std::shared_ptr<ABSNode>(new ProgramNode()));
  //nitialisation des data
  infoTree = std::shared_ptr<MetaTree>(new MetaTree());

  int ret = 0;

  static struct option long_options[] = {
    {"ast",      required_argument,       0,  'a' },
    {"metric",      required_argument,       0,  'm' },
    {"input",      required_argument,       0,  'i' },
    {"uml",      required_argument,       0,  'u' },
    {"cfg",      required_argument,       0,  'c' },
    {"dom",      required_argument,       0,  'd' },
    {"pdom",     required_argument,       0,  'p' },
    {"rea",      required_argument,       0,  'r' },
    {"cdGraph",      required_argument,       0,  'x' },
    {"ddGraph",      required_argument,       0,  'y' },
    {"fSlice",   required_argument,       0,  'f' },
    {"bSlice",   required_argument,       0,  'b' },
    {"line",     required_argument,       0,  'l' },
    {"varName",  required_argument,       0,  'v' },
    {"pdg",  required_argument,       0,  'g' },
    {0,           0,                      0,  0   }
  };

  int long_index =0;
  int opt = 0;
  while ((opt = getopt_long(argc, argv,"a:u:c:d:p:r:f:b:l:v:x:y:",
  long_options, &long_index )) != -1) {
    switch (opt) {
      case 'i' :
        input = optarg;
      break;
      case 'a' :
        ast_file = optarg;
        isRequired.insert("ast");
      break;
      case 'm' :
        metric_file = optarg;
        isRequired.insert("metric");
      break;
      case 'u' :
        uml_file = optarg;
        isRequired.insert("uml");
      break;
      case 'c' : //length = atoi(optarg);
        cfg_file = optarg;
        isRequired.insert("cfg");
        mustComputeCFG = true;
      break;
      case 'd' :
        dom_file = optarg;
        isRequired.insert("dom");
        mustComputeCFG = true;
      break;
      case 'p' :
        pdom_file = optarg;
        isRequired.insert("pdom");
        mustComputeCFG = true;
      break;
      case 'r' :
        rea_file = optarg;
        isRequired.insert("rea");
        mustComputeCFG = true;
      break;
      case 'f' :
        fSlice_file = optarg;
        isRequired.insert("fSlice");
        mustComputeCFG = true;
      break;
      case 'b' :
        bSlice_file = optarg;
        isRequired.insert("bSlice");
        mustComputeCFG = true;
      break;
      case 'l' :
        lineForSlice = atoi(optarg);
      break;
      case 'g' :
        pdG_file = optarg;
        isRequired.insert("pdg");
        mustComputeCFG = true;
      break;
      case 'v' :
        varNameForSlice = optarg;
      break;
      case 'x' :
        cdG_file = optarg;
        isRequired.insert("cdGraph");
        mustComputeCFG = true;
      break;
      case 'y' :
        ddG_file = optarg;
        isRequired.insert("ddGraph");
        mustComputeCFG = true;
      break;
      default:
        print_usage();
        exit(EXIT_FAILURE);
    }
  }

  //std::string first_argument(argv[1]);
  std::string first_argument(input);
  if (first_argument.find("compile_commands.json")!=std::string::npos) {
    // Multiple files compilation
    clang::tooling::CompilationDatabase* compilation_database;
    //std::string path(argv[1]);
    std::string path(input);
    std::string base_directory = path.substr(0, path.find_last_of("/\\"));
    std::string base_filename = path.substr(base_directory.size()+1);
    if (base_filename == "compile_commands.json") {
      std::string error_message;
      compilation_database =
        (clang::tooling::CompilationDatabase *) clang::tooling::CompilationDatabase::autoDetectFromDirectory(
          llvm::StringRef(path.c_str()),
          error_message
        );
      if (!compilation_database) {
        throw std::invalid_argument("Wrong compilation database file. Clang tooling returned '" + error_message + "'.");
      }
      nb_files = compilation_database->getAllFiles().size();
    } else {
      throw std::invalid_argument("The argument must be a compilation command prefixed by -- (example: ./a.out -- clang++ main.cpp) or must be a compilation database file ('compile_commands.json').");
    }

    clang::tooling::ClangTool tool(*compilation_database, compilation_database->getAllFiles());
    ret = tool.run(clang::tooling::newFrontendActionFactory<MyFrontendAction>());

  }
  else {
    // Single file compilation

    nb_files = 1;
    std::vector<std::string> CommandLine;
    CommandLine.push_back("clang-tool");
    CommandLine.push_back("-c");
    // for (unsigned int i = 1; i < argc; ++i) {
    //   CommandLine.push_back(std::string(argv[i]));
    // }
    //CommandLine.push_back(std::string(argv[1]));
    CommandLine.push_back(std::string(input));

    clang::tooling::ToolInvocation invocation(
      std::move(CommandLine),
      new MyFrontendAction, // Takes ownership of the pointer
      new clang::FileManager(clang::FileSystemOptions()) // Takes ownership of the pointer
    );
    ret = invocation.run();
  }


  CFGVisitor printCFG;
  if (mustComputeCFG) {
    myAst->acceptVisitor(&printCFG);
  }

  if (isRequired.find("metric") != isRequired.end()) {
    std::ofstream myfile;
    myfile.open(metric_file);
    MetricASTVisitor metricV(myfile);
    myAst->acceptVisitor(&metricV);
    myfile.close();
  }

  if (isRequired.find("ast") != isRequired.end()) {
    std::ofstream myfile;
    myfile.open(ast_file);
    PrettyPrintASTVisitor prettyV(myfile);
    myAst->acceptVisitor(&prettyV);
    myfile.close();
  }

  if (isRequired.find("uml") != isRequired.end()) {
    std::ofstream myfile;
    myfile.open(uml_file);
    UMLASTVisitor printUML;
    myAst->acceptVisitor(&printUML);
    printUML.dump(myfile);
    myfile.close();
  }

  if (isRequired.find("cfg") != isRequired.end()) {
    std::ofstream myfile;
    myfile.open(cfg_file);
    printCFG.dump(myfile);
    myfile.close();
  }

  if (isRequired.find("dom") != isRequired.end()) {
    std::ofstream myfile;
    std::vector<CFG> graph = printCFG.getGraph();
    Dominator dom;
    myfile.open(dom_file);
    for (auto it = graph.begin(); it != graph.end(); it++) {
      myfile << *(dom.compute(&(*it))) << std::endl;
    }
    myfile.close();
  }

  if (isRequired.find("pdom") != isRequired.end()) {
    std::ofstream myfile;
    std::vector<CFG> graph = printCFG.getGraph();
    PostDominator pdom;
    myfile.open(pdom_file);
    for (auto it = graph.begin(); it != graph.end(); it++) {
      myfile << *(pdom.compute(&(*it))) << std::endl;
    }
    myfile.close();
  }

  if (isRequired.find("rea") != isRequired.end()) {
    std::ofstream myfile;
    std::vector<CFG> graph = printCFG.getGraph();
    ReachingDef rea;
    myfile.open(rea_file);
    for (auto it = graph.begin(); it != graph.end(); it++) {
      rea.compute(&(*it));
      myfile << rea << std::endl;
    }
    myfile.close();
  }

  if (isRequired.find("cdGraph") != isRequired.end()) {
    std::ofstream myfile;
    std::vector<CFG> graph = printCFG.getGraph();
    CDGraphBuilder cdbuilder;
    CFG cdGraph("myCDGraph");
    PostDominator pdom;
    myfile.open(cdG_file);
    for (auto it = graph.begin(); it != graph.end(); it++) {
      cdbuilder.build(pdom.compute(&(*it)),*it, cdGraph);
      myfile << " digraph G {" << std::endl;
      cdGraph.dump(myfile);
      myfile << "}" << std::endl;
    }
    myfile.close();
  }

  if (isRequired.find("ddGraph") != isRequired.end()) {
    std::ofstream myfile;
    myfile.open(ddG_file);
    std::vector<CFG> graph = printCFG.getGraph();
    DDGraphBuilder ddbuilder;
    CFG ddGraph("myDDGraph");
    for (auto it = graph.begin(); it != graph.end(); it++) {
      ReachingDef reaTMP;
      std::pair<std::vector<std::set<int>>, std::map<std::string,std::set<int>>> values = reaTMP.compute(&(*it));
      ddbuilder.build(&(*it), ddGraph, values.first, values.second);
      myfile << " digraph G {" << std::endl;
      ddGraph.dump(myfile);
      myfile << "}" << std::endl;
    }
    myfile.close();
  }

  if (isRequired.find("pdg") != isRequired.end()) {
    std::ofstream myfile;
    std::vector<CFG> graph = printCFG.getGraph();
    CDGraphBuilder cdbuilder;
    PostDominator pdom;
    CFG cdGraph("myDDGraph");
    DDGraphBuilder ddbuilder;
    CFG ddGraph("myDDGraph");
    myfile.open(pdG_file);
    for (auto it = graph.begin(); it != graph.end(); it++) {

      cdbuilder.build(pdom.compute(&(*it)),*it, cdGraph);

      ReachingDef reaTMP;
      std::pair<std::vector<std::set<int>>, std::map<std::string,std::set<int>>> values = reaTMP.compute(&(*it));
      ddbuilder.build(&(*it), ddGraph, values.first, values.second);

      MergeGraph merger;
      CFG pdGraph("PDG");
      merger.merge(cdGraph, ddGraph, pdGraph);
      myfile << " digraph G {" << std::endl;
      pdGraph.dump(myfile);
      myfile << "}" << std::endl;
    }
    myfile.close();
  }

  if (isRequired.find("fSlice") != isRequired.end()) {
    std::ofstream myfile;
    std::vector<CFG> graph = printCFG.getGraph();
    CDGraphBuilder cdbuilder;
    PostDominator pdom;
    CFG cdGraph("myDDGraph");
    DDGraphBuilder ddbuilder;
    CFG ddGraph("myDDGraph");
    myfile.open(fSlice_file);
    for (auto it = graph.begin(); it != graph.end(); it++) {

      cdbuilder.build(pdom.compute(&(*it)),*it, cdGraph);

      ReachingDef reaTMP;
      std::pair<std::vector<std::set<int>>, std::map<std::string,std::set<int>>> values = reaTMP.compute(&(*it));
      ddbuilder.build(&(*it), ddGraph, values.first, values.second);

      MergeGraph merger;
      CFG pdGraph("PDG");
      merger.merge(cdGraph, ddGraph, pdGraph);
      ForwardSlicer fSlicer;
      CFG fSliceGraph("FSlice");
      fSlicer.slice(varNameForSlice, lineForSlice, pdGraph, fSliceGraph);
      myfile << " digraph G {" << std::endl;
      fSliceGraph.dump(myfile);
      myfile << "}" << std::endl;
    }
    myfile.close();
  }

  if (isRequired.find("bSlice") != isRequired.end()) {
    std::ofstream myfile;
    std::vector<CFG> graph = printCFG.getGraph();
    CDGraphBuilder cdbuilder;
    PostDominator pdom;
    CFG cdGraph("myDDGraph");
    DDGraphBuilder ddbuilder;
    CFG ddGraph("myDDGraph");
    myfile.open(bSlice_file);
    for (auto it = graph.begin(); it != graph.end(); it++) {

      cdbuilder.build(pdom.compute(&(*it)),*it, cdGraph);

      ReachingDef reaTMP;
      std::pair<std::vector<std::set<int>>, std::map<std::string,std::set<int>>> values = reaTMP.compute(&(*it));
      ddbuilder.build(&(*it), ddGraph, values.first, values.second);

      MergeGraph merger;
      CFG pdGraph("PDG");
      merger.merge(cdGraph, ddGraph, pdGraph);
      BackwardSlicer bSlicer;
      CFG bSliceGraph("BSlice");
      bSlicer.slice(varNameForSlice, lineForSlice, pdGraph, bSliceGraph);
      myfile << " digraph G {" << std::endl;
      bSliceGraph.dump(myfile);
      myfile << "}" << std::endl;
    }
    myfile.close();
  }

  return ret;
}
