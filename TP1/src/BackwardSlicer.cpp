#include "BackwardSlicer.h"

const std::vector<int>& BackwardSlicer::getSuccessors(const CFG& pdGraph, int id) const
{
  return pdGraph.getPredecessor(id);
}
