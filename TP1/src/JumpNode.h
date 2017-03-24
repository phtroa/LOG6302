#pragma once

#include "ABSNode.h"

class JumpNode : public ABSNode {
public:
  JumpNode();
  ~JumpNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
