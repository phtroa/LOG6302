#pragma once

#include <string>
#include <ostream>

class CFGNode
{
  friend std::ostream& operator<<(std::ostream& o, const CFGNode& node);
  public:
    CFGNode(int id, const std::string& type);
    int getId() const;
    std::string getNodeType() const;
    void dump(std::ostream& o) const;
  private:
    int myID;
    std::string nodeType;
};
