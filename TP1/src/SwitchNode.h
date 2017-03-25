#pragma once

#include "CondNode.h"

class SwitchNode : public CondNode {
public:
  SwitchNode(int line);
  ~SwitchNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
