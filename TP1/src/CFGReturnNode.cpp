#include "CFGReturnNode.h"

#include "CFGTreeVisitor.h"

CFGReturnNode::CFGReturnNode(int begin, int end) : CFGTreeNode(begin, end)
{}

CFGReturnNode::~CFGReturnNode()
{}

bool CFGReturnNode::isLinkNeeded() const
{
  return false;
}

void CFGReturnNode::acceptVisitor(CFGTreeVisitor* visitor)
{
  visitor->visit(this);
}
