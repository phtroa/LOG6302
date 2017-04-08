#pragma once

#include "ForwardSlicer.h"

class BackwardSlicer : public ForwardSlicer
{
private:
  virtual const std::vector<int>& getSuccessors(const CFG& pdGraph, int id) const;
};
