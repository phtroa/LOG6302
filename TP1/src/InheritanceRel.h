#pragma once

#include <utility>
#include <vector>

#include "ABSUMLRelation.h"

class InheritanceRel : public ABSUMLRelation
{
  public:
    InheritanceRel(const std::string& arrh = "\"empty\"");
    virtual void dump(std::ostream& o) const;
  private:
    std::string arrowhead;
};
