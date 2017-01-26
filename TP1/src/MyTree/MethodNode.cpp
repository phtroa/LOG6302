#include "MethodNode.h"

MethodNode::MethodNode(std::weak_ptr<ABSNode> parent) : ABSNode(parent) {
}

//Ces méthodes transmettent la modification à leur parent
void MethodNode::incrCond() {
  nbCond++;
}

void MethodNode::incrLoop() {
  nbLoop++;
}

void MethodNode::incrJump()  {
  nbJump++;
}

void MethodNode::incrVar() {
  nbVar++;
}
