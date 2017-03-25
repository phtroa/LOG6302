#include "CondNode.h"

#include "ABSASTVisitor.h"

#include <iostream>

CondNode::CondNode(int line) : ABSNode(line) {
}

CondNode::~CondNode()
{
}

void CondNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
    visitor->visitBetween(this);
  }
  visitor->visitPost(this);
}
