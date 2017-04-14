#pragma once

#include <string>
#include <ostream>

#include "VarInStament.h"

//Represent a node in the graph
class CFGNode
{
  friend std::ostream& operator<<(std::ostream& o, const CFGNode& node);
  public:
    CFGNode(int id, const std::string& type, int line);
    int getId() const;
    void setId(int id);
    int getLineNumber() const;
    virtual bool isAssignement() const;
    virtual std::string getLValueName() const; //return the name of the var at the  left in an assignement if any
    std::string getNodeType() const;
    virtual void dump(std::ostream& o) const;
    virtual CFGNode* clone() const;

    VarInStament getVars() const; //return all the variables used in right part
    void setVars(const VarInStament & vars);
  protected:
    VarInStament vars;
  private:
    int myID;
    std::string nodeType;
    int line_number;
};
