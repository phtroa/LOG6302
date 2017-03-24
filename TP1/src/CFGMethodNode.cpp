#include "CFGMethodNode.h"

#include "CFGTreeVisitor.h"

CFGMethodNode::CFGMethodNode(int begin, int end) : CFGTreeNode(begin, end)
{}

CFGMethodNode::~CFGMethodNode()
{}

void CFGMethodNode::acceptVisitor(CFGTreeVisitor* visitor)
{
  visitor->visit(this);
}
