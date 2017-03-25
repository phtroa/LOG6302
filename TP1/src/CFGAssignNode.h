#pragma once

#include "CFGNode.h"

class CFGAssignNode : public CFGNode
{
  public:
    CFGAssignNode(int id, const std::string& type,
                  const std::string& name, int line);
    virtual bool isAssignement() const;
    virtual std::string getLValueName() const;
    virtual void dump(std::ostream& o) const;
  private:
    std::string varName;
};
