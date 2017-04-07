#pragma once

#include "CFG.h"

#include <map>
#include <set>
#include <string>
#include <vector>

class ForwardSlicer
{
public:
  void slice(const std::string& varName, int lineNumber,
            const CFG& pdGraph, CFG& sliceOUT);
private:
  int findBeginOfSlice(const std::string& varName, int lineNumber, const CFG& pdGraph);
  virtual const std::vector<int>& getSuccessors(const CFG& pdGraph, int id) const;
};
