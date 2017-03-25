#pragma once

#include "JumpNode.h"

class BreakNode : public JumpNode {
public:
  BreakNode(int line);
  ~BreakNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
