#pragma once

#include <string>
#include <iostream>

#include "ABSASTVisitor.h"

//Compute the metric on a program
class MetricASTVisitor : public ABSASTVisitor {
public:
  MetricASTVisitor();
  ~MetricASTVisitor();
    virtual void visitPre(ClassNode* node);
    virtual void visitPre(CondNode* node);
    virtual void visitPre(BreakNode* node);
    virtual void visitPre(ContinueNode* node);
    virtual void visitPre(LoopNode* node);
    virtual void visitPre(MethodNode* node);
    virtual void visitPre(VarNode* node);

    virtual void visitPost(ClassNode* node);
    virtual void visitPost(MethodNode* node);

private:
  int currId;
  int nbIf;
  int nbLoop;
  int nbJump;
  int nbVar;

  std::string fileName;
  std::string className;

  std::string oldFileName;
  std::string oldClassName;
};
