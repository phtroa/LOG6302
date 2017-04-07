#pragma once

#include "CFG.h"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

class ReachingDef
{
  friend std::ostream& operator<<(std::ostream& o, const ReachingDef& rea);
public:
  ReachingDef();
  ~ReachingDef();

std::pair<std::vector<std::set<int>>, std::map<std::string,std::set<int>>> compute(CFG* cfg);
  virtual void dump(std::ostream& o) const;
private:
  void fillMap();
  void fillGen();
  void fillKill();
  void iterate();

  CFG* cfg;

  std::set<int>* in;
  std::set<int>* out;
  std::set<int>* gen;
  std::set<int>* kill;
  std::map<std::string,std::set<int>> varNameToSet;
};
