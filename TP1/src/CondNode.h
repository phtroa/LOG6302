#pragma once

#include "ABSNode.h"

class CondNode : public ABSNode {
public:
  CondNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
