#include "ForNode.h"

#include "ABSASTVisitor.h"

ForNode::ForNode(int line) : LoopNode(line)
{
}

ForNode::~ForNode()
{
}

void ForNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
    visitor->visitBetween(this);
  }
  visitor->visitPost(this);
}
