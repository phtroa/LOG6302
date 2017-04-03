#pragma once

#include "CFG.h"
#include "DomTree.h"

#include <algorithm>
#include <memory>
#include <utility>
#include <set>


class CDGraphBuilder
{
public:
  void build(std::shared_ptr<DomTree> pTree,const CFG& graphIN, CFG& graphOUT);
  void builS(std::vector<std::pair<int,int>>& S, std::shared_ptr<DomTree> pTree, const CFG& graphIN);
  void dumpS(std::ostream& o, const std::vector<std::pair<int,int>>& S) const;
};
