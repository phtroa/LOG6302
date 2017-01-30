#pragma once

#include <memory>

#include "ABSNode.h"
#include "ABSASTVisitor.h"

class ASTTree {
public:
  void setRoot(std::shared_ptr<ABSNode> root);
  std::shared_ptr<ABSNode> getRoot();

  void linkParentToChild(std::shared_ptr<ABSNode> parent,
     std::shared_ptr<ABSNode> child);

  void acceptVisitor(ABSASTVisitor* visitor);

private:
  std::shared_ptr<ABSNode> root;
};
