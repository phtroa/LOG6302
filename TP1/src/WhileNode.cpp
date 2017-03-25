#include "WhileNode.h"

WhileNode::WhileNode(int line) : LoopNode(line)
{}

WhileNode::~WhileNode()
{}

void WhileNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
  }
  visitor->visitPost(this);
}
