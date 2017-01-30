#include "JumpNode.h"

#include "ABSASTVisitor.h"

JumpNode::JumpNode() : ABSNode() {
}

void JumpNode::acceptVisitor(ABSASTVisitor* visitor) {
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
  }
  visitor->visitPost(this);
}
