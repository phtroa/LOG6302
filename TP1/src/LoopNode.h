#pragma once

#include "ABSNode.h"

class LoopNode : public ABSNode {
public:
  LoopNode();
  ~LoopNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
