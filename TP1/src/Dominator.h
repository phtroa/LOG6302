#pragma once

#include "CFG.h"
#include "CFGNode.h"
#include "DomTree.h"

#include <vector>
#include <memory>
#include <set>

class Dominator
{
public:
  Dominator();
  std::shared_ptr<DomTree> compute(CFG* cfg);
private:
  void makeDFSTree();
  void makeDomTree();
  int nca(int node1, int node2);
  std::shared_ptr<DomTree> convertToCFG();

  CFG* cfg;
  int* domTreeParent;
  std::set<int> treeNodes;
  int entry;
  int exit;
};
