#include "ContinueNode.h"

#include "ABSASTVisitor.h"

ContinueNode::ContinueNode() : JumpNode() {
}

ContinueNode::~ContinueNode() {
}

void ContinueNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
  }
  visitor->visitPost(this);
}
