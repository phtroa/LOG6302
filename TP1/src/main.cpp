#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>

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
int main(int argc, const char **argv) {

  if (argc <= 1) {
    throw std::invalid_argument("No argument passed");
  }

  //Initialisation de l'arbre
  myAst = std::shared_ptr<ASTTree>(new ASTTree());
  myAst->setRoot(std::shared_ptr<ABSNode>(new ProgramNode()));
  //nitialisation des data
  infoTree = std::shared_ptr<MetaTree>(new MetaTree());

  int ret = 0;

  std::string first_argument(argv[1]);
  if (first_argument.find("compile_commands.json")!=std::string::npos) {
    // Multiple files compilation
    clang::tooling::CompilationDatabase* compilation_database;
    std::string path(argv[1]);
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
    for (unsigned int i = 1; i < argc; ++i) {
      CommandLine.push_back(std::string(argv[i]));
    }

    clang::tooling::ToolInvocation invocation(
      std::move(CommandLine),
      new MyFrontendAction, // Takes ownership of the pointer
      new clang::FileManager(clang::FileSystemOptions()) // Takes ownership of the pointer
    );
    ret = invocation.run();
  }

  std::cout << "================================================================" << std::endl;
  //we compute metric
  MetricASTVisitor metricV;
  myAst->acceptVisitor(&metricV);


  std::cout << "################################AST#############################" << std::endl;
  //Print the tree (for debug purpose)
  PrettyPrintASTVisitor printAST;
  myAst->acceptVisitor(&printAST);


  std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << std::endl;
  //Print the dot file
  UMLASTVisitor printUML;
  myAst->acceptVisitor(&printUML);


  std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
  //Print the dot file
  CFGVisitor printCFG;
  myAst->acceptVisitor(&printCFG);
  printCFG.dump(std::cout);

  std::cout << "--------------------------------DOM-----------------------------" << std::endl;
  std::vector<CFG> graph = printCFG.getGraph();
  Dominator dom;
  for (auto it = graph.begin(); it != graph.end(); it++) {
    std::cout << *(dom.compute(&(*it))) << std::endl;
  }

   std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PDOM~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  PostDominator pdom;
  for (auto it = graph.begin(); it != graph.end(); it++) {
    std::cout << *(pdom.compute(&(*it))) << std::endl;
  }

  std::cout << "________________________________________________________________" << std::endl;
  ReachingDef rea;
  for (auto it = graph.begin(); it != graph.end(); it++) {
    rea.compute(&(*it));
    std::cout << rea << std::endl;
  }

  std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
  CDGraphBuilder cdbuilder;
  CFG cdGraph("myCDGraph");
  for (auto it = graph.begin(); it != graph.end(); it++) {
    cdbuilder.build(pdom.compute(&(*it)),*it, cdGraph);
    std::cout << " digraph G {" << std::endl;
    cdGraph.dump(std::cout);
    std::cout << "}" << std::endl;
  }

  std::cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << std::endl;
  DDGraphBuilder ddbuilder;
  CFG ddGraph("myDDGraph");
  for (auto it = graph.begin(); it != graph.end(); it++) {
    ReachingDef reaTMP;
    std::pair<std::vector<std::set<int>>, std::map<std::string,std::set<int>>> values = reaTMP.compute(&(*it));
    ddbuilder.build(&(*it), ddGraph, values.first, values.second);
    std::cout << " digraph G {" << std::endl;
    ddGraph.dump(std::cout);
    std::cout << "}" << std::endl;
  }

  std::cout << ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;" << std::endl;
  MergeGraph merger;
  CFG pdGraph("PDG");
  merger.merge(cdGraph, ddGraph, pdGraph);
  std::cout << " digraph G {" << std::endl;
  pdGraph.dump(std::cout);
  std::cout << "}" << std::endl;

  std::cout << "----------------------------------------------------------------" << std::endl;
  ForwardSlicer fSlicer;
  CFG fSliceGraph("FSlice");
  fSlicer.slice("inword", 10, pdGraph, fSliceGraph);
  std::cout << " digraph G {" << std::endl;
  fSliceGraph.dump(std::cout);
  std::cout << "}" << std::endl;

  std::cout << ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,," << std::endl;
  std::cout << " digraph G {" << std::endl;
  pdGraph.dumpReverse(std::cout);
  std::cout << "}" << std::endl;

  std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << std::endl;
  BackwardSlicer bSlicer;
  CFG bSliceGraph("BSlice");
  bSlicer.slice("inword", 22, pdGraph, bSliceGraph);
  std::cout << " digraph G {" << std::endl;
  bSliceGraph.dump(std::cout);
  std::cout << "}" << std::endl;


  return ret;
}
