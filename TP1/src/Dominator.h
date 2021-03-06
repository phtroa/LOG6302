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
protected:
  CFG* cfg;
  void makeDFSTree();
  void makeDomTree();
  virtual const std::vector<int>& getSuccessors(int id);
  virtual const std::vector<int>& getPredecessor(int id);

  virtual int getEntry() const;
  virtual int getExit() const;

  int nca(int node1, int node2);
  std::shared_ptr<DomTree> convertToCFG();

  int* domTreeParent;
  std::set<int> treeNodes;
  int entry;
  int exit;
};
