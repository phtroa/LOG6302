#include "AttributeNode.h"

#include "ABSASTVisitor.h"

AttributeNode::AttributeNode(const std::string& name,
                            const InfoType& type,
                            int line,
                            int visibility)
: ABSNode(line), attName(name), ifType(type), attVsblt(visibility)
{
}

AttributeNode::~AttributeNode()
{
}

std::string AttributeNode::getAttName() const {
  return attName;
}

const InfoType& AttributeNode::getType() const {
  return ifType;
}

int AttributeNode::getVisibility() const {
  return attVsblt;
}

void AttributeNode::setAttName(const std::string& name) {
  attName = name;
}

void AttributeNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
    visitor->visitBetween(this);
  }
  visitor->visitPost(this);
}
