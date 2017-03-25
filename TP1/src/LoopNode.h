#pragma once

#include "ABSNode.h"

class LoopNode : public ABSNode {
public:
  LoopNode(int line);
  ~LoopNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
