#include "CFGLoopNode.h"
#include "CFGTreeVisitor.h"


CFGLoopNode::CFGLoopNode(int begin, int end, int cond) : CFGTreeNode(begin, end), condID(cond)
{}

CFGLoopNode::~CFGLoopNode()
{}

void CFGLoopNode::acceptVisitor(CFGTreeVisitor* visitor)
{
  visitor->visit(this);
}

int CFGLoopNode::getCondID() const
{
  return condID;
}
