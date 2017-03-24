#include "NamespaceNode.h"

#include "ABSASTVisitor.h"

NamespaceNode::NamespaceNode(const std::string& name, const std::string& id)
: ABSNode(), namespaceName(name), namespaceId(id)
{
}

NamespaceNode::~NamespaceNode()
{
}

std::string NamespaceNode::getName() const {
  return namespaceName;
}

void NamespaceNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
    visitor->visitBetween(this);
  }
  visitor->visitPost(this);
}
