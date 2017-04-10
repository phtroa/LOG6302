#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>

#include "ABSASTVisitor.h"
#include "CFGNode.h"
#include "CFGAssignNode.h"
#include "CFG.h"

//Compute the CFG
class CFGVisitor : public ABSASTVisitor {
public:
  CFGVisitor();
  ~CFGVisitor();
    virtual void visitPre(AssignNode* node);
    virtual void visitPre(VarNode* node);
    virtual void visitPre(IfNode* node);
    virtual void visitPre(SwitchNode* node);
    virtual void visitPre(BreakNode* node);
    virtual void visitPre(CaseNode* node);
    virtual void visitPre(ContinueNode* node);
    virtual void visitPre(WhileNode* node);
    virtual void visitPre(DoWhileNode* node);
    virtual void visitPre(ForNode* node);
    virtual void visitPre(FuncCall* node);
    virtual void visitPre(MethodNode* node);
    virtual void visitPre(BlockNode* node);
    virtual void visitPre(ReturnNode* node);

    virtual void visitBetween(IfNode* node);

    virtual void visitPost(MethodNode* node);
    virtual void visitPost(AssignNode* node);
    virtual void visitPost(CaseNode* node);
    virtual void visitPost(VarNode* node);
    virtual void visitPost(IfNode* node);
    virtual void visitPost(SwitchNode* node);
    virtual void visitPost(WhileNode* node);
    virtual void visitPost(DoWhileNode* node);
    virtual void visitPost(ForNode* node);
    virtual void visitPost(FuncCall* node);
    virtual void visitPost(ProgramNode* node);
    virtual void visitPost(BlockNode* node);
    virtual void visitPost(ReturnNode* node);

    std::vector<CFG>& getGraph();
    void dump(std::ostream& o) const;
private:
  int globalID;
  int localID;

  int entryID;
  int exitID;
  int currID;

  std::vector<CFG> graph;
  std::vector<int> loopStackBegin;
  std::vector<int> condStack;
  std::vector<int> loopStackEnd;
  std::vector<int> ifStackBegin;
  std::vector<int> ifStackEnd;
  std::vector<int> stackBegin;
  std::vector<int> stackEnd;

  bool needlink;
};
