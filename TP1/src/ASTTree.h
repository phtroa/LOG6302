#pragma once

#include <memory>
#include "ABSNode.h"

class ASTTree {
public:
  ASTTree();
  void setRoot(std::shared_ptr<ABSNode> root);
  void getRoot();

private:
  std::shared_ptr<ABSNode> root;
};
