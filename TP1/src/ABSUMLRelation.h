#pragma once

#include <utility>
#include <vector>
#include <ostream>

class ABSUMLRelation
{
  public:
    void link(const std::string& derivedClassName, const std::string& baseClassName);
    virtual void dump(std::ostream& o) const = 0;
  protected:
    std::vector<std::pair<std::string,std::string>> allLinks;
};
