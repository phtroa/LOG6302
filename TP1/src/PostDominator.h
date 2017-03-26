#pragma once

#include "Dominator.h"
#include "CFG.h"
#include "CFGNode.h"
#include "DomTree.h"

#include <vector>
#include <memory>
#include <set>

class PostDominator : public Dominator
{
public:
  PostDominator();
protected:
  virtual const std::vector<int>& getSuccessors(int id);
  virtual const std::vector<int>& getPredecessor(int id);

  virtual int getEntry() const;
  virtual int getExit() const;
};
