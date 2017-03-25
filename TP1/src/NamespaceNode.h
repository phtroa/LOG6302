#pragma once

#include "ABSNode.h"

#include <string>

class NamespaceNode : public ABSNode {
public:
    NamespaceNode(const std::string& name, const std::string& id, int line);
    ~NamespaceNode();

    std::string getName() const;
    std::string getId() const;

    void acceptVisitor(ABSASTVisitor* visitor);
private:
  std::string namespaceName;
  std::string namespaceId;
};
