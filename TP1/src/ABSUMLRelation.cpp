#include "ABSUMLRelation.h"

void ABSUMLRelation::link(const std::string& derivedClassName, const std::string& baseClassName)
{
  allLinks.push_back(std::make_pair(derivedClassName, baseClassName));
}
