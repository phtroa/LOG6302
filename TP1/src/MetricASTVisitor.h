#pragma once

#include <string>
#include <iostream>

#include "ABSASTVisitor.h"

//Compute the metric on a program
class MetricASTVisitor : public ABSASTVisitor {
public:
  MetricASTVisitor(std::ostream& stream);
  ~MetricASTVisitor();
    virtual void visitPre(ClassNode* node);
    virtual void visitPre(IfNode* node);
    virtual void visitPre(SwitchNode* node);
    virtual void visitPre(BreakNode* node);
    virtual void visitPre(ContinueNode* node);
    virtual void visitPre(ForNode* node);
    virtual void visitPre(WhileNode* node);
    virtual void visitPre(DoWhileNode* node);
    virtual void visitPre(MethodNode* node);
    virtual void visitPre(VarNode* node);

    virtual void visitPost(ClassNode* node);
    virtual void visitPost(MethodNode* node);

private:

  std::ostream& o;

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
