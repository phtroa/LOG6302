#pragma once

#include "CFG.h"

#include <memory>
#include <set>

class MergeGraph
{
public:
  void merge(const CFG& fgraph, const CFG& sgraph, CFG& res);
};
