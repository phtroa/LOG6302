#pragma once

#include <string>
#include <iostream>

#include "ABSASTVisitor.h"

//Produces a dump of the tree while showing its structure
class PrettyPrintASTVisitor : public ABSASTVisitor {
public:
  PrettyPrintASTVisitor(std::ostream& stream);
  ~PrettyPrintASTVisitor();
    virtual void visitPre(ClassNode* node);
    virtual void visitPre(CondNode* node);
    virtual void visitPre(BreakNode* node);
    virtual void visitPre(ContinueNode* node);
    virtual void visitPre(WhileNode* node);
    virtual void visitPre(DoWhileNode* node);
    virtual void visitPre(ForNode* node);
    virtual void visitPre(MethodNode* node);
    virtual void visitPre(ProgramNode* node);
    virtual void visitPre(VarNode* node);
    virtual void visitPre(AttributeNode* node);
    virtual void visitPre(AssignNode* node);
    virtual void visitPre(NamespaceNode* node);
    virtual void visitPre(ReturnNode* node);
    virtual void visitPre(BlockNode* node);

    virtual void visitPost(ClassNode* node);
    virtual void visitPost(CondNode* node);
    virtual void visitPost(BreakNode* node);
    virtual void visitPost(ContinueNode* node);
    virtual void visitPost(WhileNode* node);
    virtual void visitPost(DoWhileNode* node);
    virtual void visitPost(ForNode* node);
    virtual void visitPost(MethodNode* node);
    virtual void visitPost(ProgramNode* node);
    virtual void visitPost(VarNode* node);
    virtual void visitPost(AttributeNode* node);
    virtual void visitPost(AssignNode* node);
    virtual void visitPost(NamespaceNode* node);
    virtual void visitPost(ReturnNode* node);
    virtual void visitPost(BlockNode* node);

private:

  std::ostream& o;

  void writeSpaces(int nb); //writes nb spaces on the screen
  int spacePadding;
};
