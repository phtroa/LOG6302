#pragma once

#include "VarInStament.h"
#include "CFG.h"

#include <algorithm>
#include <map>
#include <set>
#include <vector>

class DDGraphBuilder
{
public:
  void build(const CFG* in, CFG & out,
     const std::vector<std::set<int>> & reachingDef,
       std::map<std::string,std::set<int>> & varnameToDef);
};
