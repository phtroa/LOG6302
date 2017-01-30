#include "MethodNode.h"

#include "ABSASTVisitor.h"

MethodNode::MethodNode(const std::string& name) : ABSNode(), methodName(name) {
}

void MethodNode::setMethodName(const std::string& name) {
  methodName = name;
}

std::string MethodNode::getMethodName() const {
  return methodName;
}

void MethodNode::acceptVisitor(ABSASTVisitor* visitor) {
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
  }
  visitor->visitPost(this);
}
