#include "LoopNode.h"

#include "ABSASTVisitor.h"

LoopNode::LoopNode() : ABSNode() {
}

void LoopNode::acceptVisitor(ABSASTVisitor* visitor) {
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
  }
  visitor->visitPost(this);
}
