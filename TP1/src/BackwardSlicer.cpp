#include "BackwardSlicer.h"

const std::vector<int>& ForwardSlicer::getSuccessors(const CFG& pdGraph, int id) const
{
  return pdGraph.getPredecessor(id);
}
