#include "BreakNode.h"

#include "ABSASTVisitor.h"

BreakNode::BreakNode() : JumpNode() {
}

BreakNode::~BreakNode() {
}

void BreakNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
  }
  visitor->visitPost(this);
}
