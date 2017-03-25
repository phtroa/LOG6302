#pragma once

#include "CondNode.h"

class IfNode : public CondNode {
public:
  IfNode(int line);
  ~IfNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
