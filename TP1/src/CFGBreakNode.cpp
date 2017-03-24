#include "CFGBreakNode.h"
#include "CFGTreeVisitor.h"

CFGBreakNode::CFGBreakNode(int begin, int end) : CFGTreeNode(begin, end)
{}

CFGBreakNode::~CFGBreakNode()
{}

bool CFGBreakNode::isLinkNeeded() const
{
  return false;
}

void CFGBreakNode::acceptVisitor(CFGTreeVisitor* visitor)
{
  visitor->visit(this);
}
