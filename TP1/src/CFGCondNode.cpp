#include "CFGCondNode.h"

#include "CFGTreeVisitor.h"


CFGCondNode::CFGCondNode(int begin, int end, int cond) : CFGTreeNode(begin, end), condID(cond)
{}

CFGCondNode::~CFGCondNode()
{}

void CFGCondNode::acceptVisitor(CFGTreeVisitor* visitor)
{
  visitor->visit(this);
}

int CFGCondNode::getCondID() const
{
  return condID;
}
