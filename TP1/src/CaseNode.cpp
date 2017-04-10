#include "CaseNode.h"

#include "ABSASTVisitor.h"

CaseNode::CaseNode(int line) : BlockNode(line)
{
}

CaseNode::~CaseNode()
{
}

void CaseNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
    visitor->visitBetween(this);
  }
  visitor->visitPost(this);
}
