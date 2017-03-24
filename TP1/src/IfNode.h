#pragma once

#include "CondNode.h"

class IfNode : public CondNode {
public:
  IfNode();
  ~IfNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
