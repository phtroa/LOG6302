#pragma once

#include <string>
#include <iostream>

#include "ABSASTVisitor.h"

//Produces a dump of the tree while showing its structure
class PrettyPrintASTVisitor : public ABSASTVisitor {
public:
  PrettyPrintASTVisitor();
    virtual void visitPre(ClassNode* node);
    virtual void visitPre(CondNode* node);
    virtual void visitPre(JumpNode* node);
    virtual void visitPre(LoopNode* node);
    virtual void visitPre(MethodNode* node);
    virtual void visitPre(ProgramNode* node);
    virtual void visitPre(VarNode* node);
    virtual void visitPre(AttributeNode* node);
    virtual void visitPre(NamespaceNode* node);

    virtual void visitPost(ClassNode* node);
    virtual void visitPost(CondNode* node);
    virtual void visitPost(JumpNode* node);
    virtual void visitPost(LoopNode* node);
    virtual void visitPost(MethodNode* node);
    virtual void visitPost(ProgramNode* node);
    virtual void visitPost(VarNode* node);
    virtual void visitPost(AttributeNode* node);
    virtual void visitPost(NamespaceNode* node);

private:
  void writeSpaces(int nb); //writes nb space on the screen
  int spacePadding;
};
