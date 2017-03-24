#ifndef LOG6302_VISITOR_H
#define LOG6302_VISITOR_H

#include <iostream>
#include <string>

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTContext.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Lex/Lexer.h>

#include "ASTTree.h"
#include "AttributeNode.h"
#include "ClassNode.h"
#include "CondNode.h"
#include "BlockNode.h"
#include "IfNode.h"
#include "JumpNode.h"
#include "BreakNode.h"
#include "ContinueNode.h"
#include "LoopNode.h"
#include "ForNode.h"
#include "WhileNode.h"
#include "MetaTree.h"
#include "MethodNode.h"
#include "NamespaceNode.h"
#include "ProgramNode.h"
#include "VarNode.h"
#include "ReturnNode.h"
#include "SwitchNode.h"

#include "InfoType.h"

/**
 * LOG6302 Cette classe est un exemple d'un visiteur récursif de clang. À l'intérieur, vous pouvez y trouver deux exemples
 * de visites, et un exemple de traverse.
 */
class Visitor : public clang::RecursiveASTVisitor<Visitor> {
public:

  Visitor(clang::ASTContext &context,
     std::shared_ptr<ASTTree> ast,
     std::shared_ptr<MetaTree> info);
  // Traverses
  bool TraverseCXXMethodDecl(clang::CXXMethodDecl *D);
  bool TraverseCXXRecordDecl(clang::CXXRecordDecl *D);
  bool TraverseFieldDecl(clang::FieldDecl *D);
  bool TraverseVarDecl(clang::VarDecl *D);
  bool TraverseIfStmt(clang::IfStmt *S);
  bool TraverseCompoundStmt(clang::CompoundStmt *S);
  bool TraverseSwitchStmt(clang::SwitchStmt *S);
  bool TraverseCaseStmt(clang::CaseStmt *S);
  bool TraverseBreakStmt(clang::BreakStmt *S);
  bool TraverseContinueStmt(clang::ContinueStmt *S);
  bool TraverseForStmt(clang::ForStmt *S);
  bool TraverseWhileStmt(clang::WhileStmt *S);
  bool TraverseReturnStmt(clang::ReturnStmt *S);
  bool TraverseNamespaceDecl(clang::NamespaceDecl *D);

  std::shared_ptr<ASTTree> getAST();
  void setAST(std::shared_ptr<ASTTree> ast);

private:
  clang::ASTContext &context_;
  bool inMethod;
  int ifDepth;
  std::shared_ptr<ASTTree> myAst;
  std::shared_ptr<MetaTree> infoTree;
  std::shared_ptr<ABSNode> currNode;

  bool isHeaderSystem(clang::Decl* D) const;
  bool isInIf() const;

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
  InfoType extractedFinalType(const clang::QualType& type);
  std::string computeID(const clang::DeclContext* D) const;
  void completeBaseList(clang::CXXRecordDecl *D, std::shared_ptr<ABSNode> classNode);
};

#endif //LOG6302_VISITOR_H
