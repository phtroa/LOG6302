#include "ClassNode.h"

#include "ABSASTVisitor.h"

ClassNode::ClassNode(const std::string& name, const std::string& file)
 : className(name), filePath(file) {
}

void ClassNode::setClassName(const std::string& name) {
  className = name;
}

std::string ClassNode::getClassName() const {
  return className;
}

void ClassNode::setFilePath(const std::string& file) {
  filePath = file;
}

std::string ClassNode::getFilePath() const {
  return filePath;
}

void ClassNode::acceptVisitor(ABSASTVisitor* visitor) {
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
  }
  visitor->visitPost(this);
}
