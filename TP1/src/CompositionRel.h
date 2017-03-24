#pragma once

#include <utility>
#include <vector>

#include "ABSUMLRelation.h"

class CompositionRel : public ABSUMLRelation
{
  public:
    CompositionRel(const std::string& arrh = "normal");
    virtual void dump(std::ostream& o) const;
  private:
    std::string arrowhead;
};
