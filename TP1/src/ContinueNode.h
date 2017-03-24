#pragma once

#include "JumpNode.h"

class ContinueNode : public JumpNode {
public:
  ContinueNode();
  ~ContinueNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
