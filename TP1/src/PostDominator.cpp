#include "PostDominator.h"

PostDominator::PostDominator() : Dominator()
{
}

const std::vector<int>& PostDominator::getSuccessors(int id)
{
  return cfg->getPredecessor(id);
}

const std::vector<int>& PostDominator::getPredecessor(int id)
{
  return cfg->getSuccessors(id);
}

int PostDominator::getEntry() const
{
  return cfg->getExit();
}

int PostDominator::getExit() const
{
  return cfg->getEntry();
}
