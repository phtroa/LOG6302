#include "ABSNode.h"

  ABSNode::ABSNode() {
  }

void ABSNode::addChild(std::shared_ptr<ABSNode> child) {
  children.push_back(child);
}

void ABSNode::setParent(std::weak_ptr<ABSNode> parent) {
  this->parent = parent;
}
