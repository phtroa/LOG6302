#pragma once

#include "ABSNode.h"

class BlockNode : public ABSNode {
public:
  BlockNode();
  ~BlockNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
