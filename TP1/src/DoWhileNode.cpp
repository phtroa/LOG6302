#include "DoWhileNode.h"

#include "ABSASTVisitor.h"

DoWhileNode::DoWhileNode(int line) : LoopNode(line)
{}

DoWhileNode::~DoWhileNode()
{}

void DoWhileNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
  }
  visitor->visitPost(this);
}
