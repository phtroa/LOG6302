#include "CondNode.h"

#include "ABSASTVisitor.h"

CondNode::CondNode() : ABSNode() {
}

void CondNode::acceptVisitor(ABSASTVisitor* visitor) {
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
  }
  visitor->visitPost(this);
}
