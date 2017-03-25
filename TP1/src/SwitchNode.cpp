#include "SwitchNode.h"

#include "ABSASTVisitor.h"

SwitchNode::SwitchNode(int line) : CondNode(line) {
}

SwitchNode::~SwitchNode()
{
}

void SwitchNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
  }
  visitor->visitPost(this);
}
