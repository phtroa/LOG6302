#include "ProgramNode.h"

#include "ABSASTVisitor.h"

ProgramNode::ProgramNode() {
}

ProgramNode::~ProgramNode() {
}


void ProgramNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
    visitor->visitBetween(this);
  }
  visitor->visitPost(this);
}
