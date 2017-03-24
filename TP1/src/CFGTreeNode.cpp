#include "CFGTreeNode.h"

CFGTreeNode::CFGTreeNode(int begin, int end) : beginID(begin), endId(end)
{}

CFGTreeNode::~CFGTreeNode()
{}

int CFGTreeNode::getBeginID() const
{
  return beginID;
}

int CFGTreeNode::getEndID() const
{
  return endId;
}

bool CFGTreeNode::isLinkNeeded() const
{
  return true;
}

void CFGTreeNode::addChild(std::shared_ptr<CFGTreeNode> child)
{
  children.push_back(child);
}

void CFGTreeNode::setParent(std::weak_ptr<CFGTreeNode> parent)
{
  this->parent = parent;
}


std::shared_ptr<CFGTreeNode> CFGTreeNode::getParent() const
{
  return parent.lock();
}

std::shared_ptr<CFGTreeNode> CFGTreeNode::getNode(int i) const
{
  return children[i];
}

int CFGTreeNode::getNbChildren() const
{
  return children.size();
}
