#pragma once

#include "JumpNode.h"

class ContinueNode : public JumpNode {
public:
  ContinueNode(int line);
  ~ContinueNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
