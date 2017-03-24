#pragma once

#include "JumpNode.h"

class BreakNode : public JumpNode {
public:
  BreakNode();
  ~BreakNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
