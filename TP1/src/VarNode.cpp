#include "VarNode.h"

#include "ABSASTVisitor.h"

VarNode::VarNode(const std::string& name, int line)
  : ABSNode(line), varName(name) {
}

VarNode::~VarNode()
{
}

std::string VarNode::getVarName() const {
  return varName;
}

void VarNode::setVarName(const std::string& name) {
  varName = name;
}

void VarNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
    visitor->visitBetween(this);
  }
  visitor->visitPost(this);
}
