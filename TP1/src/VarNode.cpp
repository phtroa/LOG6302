#include "VarNode.h"

#include "ABSASTVisitor.h"

VarNode::VarNode() : ABSNode() {
}

void VarNode::acceptVisitor(ABSASTVisitor* visitor) {
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
  }
  visitor->visitPost(this);
}
