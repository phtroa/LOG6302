#pragma once

#include <string>
#include <ostream>

class CFGNode
{
  friend std::ostream& operator<<(std::ostream& o, const CFGNode& node);
  public:
    CFGNode(int id, const std::string& type, int line);
    int getId() const;
    int getLineNumber() const;
    virtual bool isAssignement() const;
    virtual std::string getLValueName() const;
    std::string getNodeType() const;
    virtual void dump(std::ostream& o) const;
    virtual CFGNode* clone() const;
  private:
    int myID;
    std::string nodeType;
    int line_number;
};
