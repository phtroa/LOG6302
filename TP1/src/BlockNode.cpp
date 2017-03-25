#include "BlockNode.h"

#include "ABSASTVisitor.h"

BlockNode::BlockNode(int line) : ABSNode(line)
{
}

BlockNode::~BlockNode()
{
}

void BlockNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
    visitor->visitBetween(this);
  }
  visitor->visitPost(this);
}
