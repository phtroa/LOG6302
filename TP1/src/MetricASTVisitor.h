#pragma once

#include <string>
#include <iostream>

#include "ABSASTVisitor.h"

class MetricASTVisitor : public ABSASTVisitor {
public:
  MetricASTVisitor();
    virtual void visitPre(ClassNode* node);
    virtual void visitPre(CondNode* node);
    virtual void visitPre(JumpNode* node);
    virtual void visitPre(LoopNode* node);
    virtual void visitPre(MethodNode* node);
    virtual void visitPre(ProgramNode* node);
    virtual void visitPre(VarNode* node);

    virtual void visitPost(ClassNode* node);
    virtual void visitPost(CondNode* node);
    virtual void visitPost(JumpNode* node);
    virtual void visitPost(LoopNode* node);
    virtual void visitPost(MethodNode* node);
    virtual void visitPost(ProgramNode* node);
    virtual void visitPost(VarNode* node);

private:
  int currId;
  int nbIf;
  int nbLoop;
  int nbJump;
  int nbVar;

  std::string fileName;
  std::string className;
};