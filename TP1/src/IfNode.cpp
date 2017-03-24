#include "IfNode.h"

#include "ABSASTVisitor.h"

IfNode::IfNode() : CondNode() {
}

IfNode::~IfNode()
{
}

void IfNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
    if (i < children.size() - 1)
      visitor->visitBetween(this);
  }
  visitor->visitPost(this);
}
