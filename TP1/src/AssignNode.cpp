#include "AssignNode.h"

#include "ABSASTVisitor.h"

AssignNode::AssignNode(const std::string& name, int line)
: ABSNode(line), varName(name)
{
}

AssignNode::~AssignNode()
{
}

const std::string& AssignNode::getVarName() const {
  return varName;
}

void AssignNode::setVarName(const std::string& name) {
  varName = name;
}

void AssignNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
    visitor->visitBetween(this);
  }
  visitor->visitPost(this);
}
