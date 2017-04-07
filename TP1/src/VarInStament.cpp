#include "VarInStament.h"

VarInStament::VarInStament()
{
}

void VarInStament::addValue(const std::string & varName)
{
  values.push_back(varName);
}

int VarInStament::getNumValues() const
{
  return values.size();
}

std::string VarInStament::getValue(int i) const
{
  return values[i];
}

bool VarInStament::hasValue() const
{
  return values.size() > 0;
}
