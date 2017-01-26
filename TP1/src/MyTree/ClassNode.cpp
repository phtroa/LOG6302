#include "ClassNode.h"

ClassNode::ClassNode(const std::string& name, std::weak_ptr<ABSNode> parent) : ABSNode(parent), className(name) {
}

void ClassNode::setClassName(const std::string& name) {
  className = name;
}

std::string ClassNode::getClassName() const {
  return className;
}
