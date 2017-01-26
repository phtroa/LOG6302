#include "ABSNode.h"

ABSNode::ABSNode(std::weak_ptr<ABSNode> parent) {
  this->parent = parent;
  if (parent != nullptr)
    parent->addchild(std::shared_ptr(this));
}

void ABSNode::addchild(std::shared_ptr<ABSNode> child) {
  children.pushback(child);
}

//Ces méthodes transmettent la modification à leur parent
void ABSNode::incrCond() {
  auto shared = parent.lock();
  if (shared != nullptr)
    shared->incrCond();
}

void ABSNode::incrLoop() {
  auto shared = parent.lock();
  if (shared != nullptr)
    shared->incrLoop();
}

void ABSNode::incrJump()  {
  auto shared = parent.lock();
  if (shared != nullptr)
    shared->incrJump();
}

void ABSNode::incrVar() {
  auto shared = parent.lock();
  if (shared != nullptr)
    shared->incrVar();
}
