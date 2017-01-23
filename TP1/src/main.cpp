#include <iostream>
#include <clang/Tooling/Tooling.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/CompilerInstance.h>

#include "Visitor.h"

static unsigned int current_file = 0;
static size_t nb_files = 0;


/******************************************************************************/
/* MyASTConsumer                                                              */
/******************************************************************************/
class MyASTConsumer : public clang::ASTConsumer {
 public:

  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
    Visitor visitor(Context);
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

  } else {
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

  return ret;
}