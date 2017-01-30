#ifndef LOG6302_VISITOR_H
#define LOG6302_VISITOR_H

#include <iostream>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTContext.h>
#include <clang/Lex/Lexer.h>
#include <clang/Frontend/CompilerInstance.h>

#include "ASTTree.h"
#include "ClassNode.h"
#include "CondNode.h"
#include "JumpNode.h"
#include "LoopNode.h"
#include "MethodNode.h"
#include "VarNode.h"
#include "ProgramNode.h"

/**
 * LOG6302 Cette classe est un exemple d'un visiteur récursif de clang. À l'intérieur, vous pouvez y trouver deux exemples
 * de visites, et un exemple de traverse.
 */
class Visitor : public clang::RecursiveASTVisitor<Visitor> {
public:

  Visitor(clang::ASTContext &context);

  // Visites
  bool VisitCXXRecordDecl(clang::CXXRecordDecl *D);
  //variables
  bool VisitVarDecl(clang::VarDecl *VD);
  //conditions
  bool VisitIfStmt(clang::IfStmt *S);
  bool VisitSwitchStmt(clang::SwitchStmt *S);
  //Sauts
  bool VisitBreakStmt(clang::BreakStmt *S);
  bool VisitContinueStmt(clang::ContinueStmt *S);
  //boucles
  bool VisitForStmt(clang::ForStmt *S);
  bool VisitWhileStmt(clang::WhileStmt *S);

  // Traverses
  bool TraverseCXXMethodDecl(clang::CXXMethodDecl *D);
  bool TraverseCXXRecordDecl(clang::CXXRecordDecl *D);
  bool TraverseVarDecl(clang::VarDecl *D);
  bool TraverseIfStmt(clang::IfStmt *S);
  bool TraverseSwitchStmt(clang::SwitchStmt *S);
  bool TraverseBreakStmt(clang::BreakStmt *S);
  bool TraverseContinueStmt(clang::ContinueStmt *S);
  bool TraverseForStmt(clang::ForStmt *S);
  bool TraverseWhileStmt(clang::WhileStmt *S);

  std::shared_ptr<ASTTree> getAST();

private:
  clang::ASTContext &context_;
  bool inClass;
  std::shared_ptr<ASTTree> myAst;
  std::shared_ptr<ABSNode> currNode;

  std::string GetStatementString(clang::Stmt *S) {
    bool invalid;
    if (!S) return "Something";

    clang::CharSourceRange conditionRange = clang::CharSourceRange::getTokenRange(S->getLocStart(), S->getLocEnd());
    std::string str = clang::Lexer::getSourceText(conditionRange, context_.getSourceManager(), context_.getLangOpts(), &invalid);
    if (invalid)
      return "Something";
    encode(str);
    return str;
  }

  void encode(std::string& data) {
    std::string buffer;
    buffer.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
      switch(data[pos]) {
        case '&':  buffer.append("&amp;");       break;
        case '\"': buffer.append("&quot;");      break;
        case '\'': buffer.append("&apos;");      break;
        case '<':  buffer.append("&lt;");        break;
        case '>':  buffer.append("&gt;");        break;
        case '\n':  buffer.append("\\n");        break;
        case '\\':  buffer.append("\\\\");        break;
        case '|':  buffer.append("\\|");        break;
        default:   buffer.append(&data[pos], 1); break;
      }
    }
    data.swap(buffer);
  }
};


#endif //LOG6302_VISITOR_H
