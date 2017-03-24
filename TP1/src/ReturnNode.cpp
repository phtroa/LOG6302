#include "ReturnNode.h"

#include "ABSASTVisitor.h"

ReturnNode::ReturnNode() : ABSNode() {
}

ReturnNode::~ReturnNode()
{
}

void ReturnNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
    visitor->visitBetween(this);
  }
  visitor->visitPost(this);
}
