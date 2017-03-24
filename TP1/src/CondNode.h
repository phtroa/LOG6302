#pragma once

#include "ABSNode.h"

class CondNode : public ABSNode {
public:
  CondNode();
  ~CondNode();

  virtual void acceptVisitor(ABSASTVisitor* visitor);
};
