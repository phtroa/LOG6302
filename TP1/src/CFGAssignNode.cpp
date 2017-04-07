#include "CFGAssignNode.h"

CFGAssignNode::CFGAssignNode(int id, const std::string& type,
                              const std::string& name, int line)
                              : CFGNode(id, type, line), varName(name)
{
}

bool CFGAssignNode::isAssignement() const
{
  return true;
}

std::string CFGAssignNode::getLValueName() const
{
  return varName;
}

CFGNode* CFGAssignNode::clone() const
{
  return new CFGAssignNode(*this);
}

void CFGAssignNode::dump(std::ostream& o) const
{
  std::string idInGraph;
  idInGraph = std::to_string(getId());
  o << idInGraph << " [" << std::endl;
  o << "label=\"" << getNodeType() << " at line : "
  << getLineNumber() << ", varName = "
  << varName << std::endl;
  o << "Var used : ";
  for (int i  = 0; i < vars.getNumValues(); i ++) {
    o << " " << vars.getValue(i) << " ";
  }
  o << "\"" << std::endl;
  o << "]" << std::endl;
}
