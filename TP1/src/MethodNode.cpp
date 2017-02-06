#include "MethodNode.h"

#include "ABSASTVisitor.h"

MethodNode::MethodNode(const std::string& myClassName, const std::string& myfName)
: ABSNode(), methodName(myClassName), fileName(myfName) {
}

void MethodNode::setMethodName(const std::string& name) {
  methodName = name;
}

std::string MethodNode::getMethodName() const {
  return methodName;
}

void MethodNode::setFileName(const std::string& name) {
  fileName = name;
}

std::string MethodNode::getFileName() const {
  return fileName;
}

void MethodNode::acceptVisitor(ABSASTVisitor* visitor) {
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
  }
  visitor->visitPost(this);
}
