#pragma once

#include "CondNode.h"

class SwitchNode : public CondNode {
public:
  SwitchNode();
  ~SwitchNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
