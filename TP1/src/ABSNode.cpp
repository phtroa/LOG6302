#include "ABSNode.h"
#include "ABSASTVisitor.h"

ABSNode::ABSNode(int line) : line_number(line)
{
}

ABSNode::~ABSNode()
{
}

void ABSNode::addChild(std::shared_ptr<ABSNode> child)
{
  children.push_back(child);
}

void ABSNode::setParent(std::weak_ptr<ABSNode> parent)
{
  this->parent = parent;
}


std::shared_ptr<ABSNode> ABSNode::getParent() const
{
  return parent.lock();
}

void ABSNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (auto it = children.begin(); it != children.end(); it++) {
    (*it)->acceptVisitor(visitor);
  }
  visitor->visitPost(this);
}

int ABSNode::getNbChildren() const {
  return children.size();
}


int ABSNode::getLineNumber() const {
  return line_number;
}
