#pragma once

#include "ABSNode.h"

class BlockNode : public ABSNode {
public:
  BlockNode(int line);
  ~BlockNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
