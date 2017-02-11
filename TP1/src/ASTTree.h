#pragma once

#include <memory>

#include "ABSNode.h"
#include "ABSASTVisitor.h"

//Represent the Tree
class ASTTree {
public:
  void setRoot(std::shared_ptr<ABSNode> root);
  std::shared_ptr<ABSNode> getRoot();

  //add the child to the parent and the other way around
  void linkParentToChild(std::shared_ptr<ABSNode> parent,
     std::shared_ptr<ABSNode> child);

  void acceptVisitor(ABSASTVisitor* visitor);

private:
  std::shared_ptr<ABSNode> root;
};
