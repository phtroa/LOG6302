#pragma once

#include <vector>
#include "CFG.h"

class CFGBlockNode;
class CFGBreakNode;
class CFGCondNode;
class CFGLoopNode;
class CFGReturnNode;
class CFGMethodNode;

class CFGTreeVisitor
{
public:
  CFGTreeVisitor(CFG* cfg);
  void visit(const CFGBlockNode* node);
  void visit(const CFGBreakNode* node);
  void visit(const CFGCondNode* node);
  void visit(const CFGLoopNode* node);
  void visit(const CFGReturnNode* node);
  void visit(const CFGMethodNode* node);
private:
  std::vector<int> loopEndStack;
  std::vector<int> loopBeginStack;
  int entryID;
  int exitID;
  CFG* currCFG;
};
