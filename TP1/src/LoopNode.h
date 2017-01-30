#pragma once

#include "ABSNode.h"

class LoopNode : public ABSNode {
public:
  LoopNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
