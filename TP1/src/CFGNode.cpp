#include "CFGNode.h"

#include <string>

CFGNode::CFGNode(int id, const std::string& type, int line) : myID(id), nodeType(type), line_number(line)
{
}

int CFGNode::getId() const
{
  return myID;
}

int CFGNode::getLineNumber() const
{
  return line_number;
}

std::string CFGNode::getNodeType() const
{
  return nodeType;
}


void CFGNode::dump(std::ostream& o) const
{
  std::string idInGraph;
  idInGraph = std::to_string(getId());
  o << idInGraph << " [" << std::endl;
  o << "label=\"" << getNodeType() << " at line : " << getLineNumber() << "\"" << std::endl;
  o << "]" << std::endl;
}

std::ostream& operator<<(std::ostream& o, const CFGNode& node) {
  node.dump(o);

  return o;
}
