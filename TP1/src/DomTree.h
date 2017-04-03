#pragma once

#include <vector>
#include <iostream>
#include <utility>

#include "CFGNode.h"

class DomTree
{
  friend std::ostream& operator<<(std::ostream& o, const DomTree& tree);
public:
  DomTree(const std::vector<CFGNode*>& nodes, int* links, int size);
  void dump(std::ostream& o) const;
  std::vector<std::pair<int,int>>& getS();
  std::vector<CFGNode*>& getNodes();
  int getSize() const;
  CFGNode* getNode(int i);
  void dumpS(std::ostream& o) const;
  int getiDom(int x) const;
  bool inS(int x, int y) const;
private:
  std::vector<CFGNode*> mNodes;
  //mLinks[i] is the direct parent of i in the tree
  std::vector<int> mLinks;
};
