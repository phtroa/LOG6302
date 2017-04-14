#pragma once

#include "CFGNode.h"

//represents a node that symbolized a line such as:
//x = stuff
class CFGAssignNode : public CFGNode
{
  public:
    CFGAssignNode(int id, const std::string& type,
                  const std::string& name, int line);
    virtual bool isAssignement() const;
    virtual std::string getLValueName() const;
    virtual void dump(std::ostream& o) const;
    virtual CFGNode* clone() const; //create a deep copy
  private:
    std::string varName; // the name of the var which is written would be "x" in the above example
};
