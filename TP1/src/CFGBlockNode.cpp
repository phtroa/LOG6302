#include "CFGBlockNode.h"
#include "CFGTreeVisitor.h"

CFGBlockNode::CFGBlockNode()
: CFGTreeNode(0,0)
{}

CFGBlockNode::~CFGBlockNode()
{}

void CFGBlockNode::acceptVisitor(CFGTreeVisitor* visitor)
{
  visitor->visit(this);
}

int CFGBlockNode::getBeginID() const
{
  return getNode(0)->getBeginID();
}

int CFGBlockNode::getEndID() const
{
  return getNode(getNbChildren()-1)->getEndID();
}

bool CFGBlockNode::isLinkNeeded() const
{
  return getNode(getNbChildren()-1)->isLinkNeeded();
}
