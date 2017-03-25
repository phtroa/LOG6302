#include "JumpNode.h"

#include "ABSASTVisitor.h"

JumpNode::JumpNode(int line) : ABSNode(line) {
}

JumpNode::~JumpNode() {
}

void JumpNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
    visitor->visitBetween(this);
  }
  visitor->visitPost(this);
}
