#pragma once

#include <vector>
#include <iostream>

#include "CFGNode.h"

class DomTree
{
  friend std::ostream& operator<<(std::ostream& o, const DomTree& tree);
public:
  DomTree(const std::vector<CFGNode*>& nodes, int* links, int size);
  void dump(std::ostream& o) const;
private:
  std::vector<CFGNode*> mNodes;
  std::vector<int> mLinks;
};
