#pragma once

#include "ABSNode.h"

class JumpNode : public ABSNode {
public:
  JumpNode(int line);
  ~JumpNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
