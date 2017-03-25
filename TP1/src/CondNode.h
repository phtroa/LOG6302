#pragma once

#include "ABSNode.h"

class CondNode : public ABSNode {
public:
  CondNode(int line);
  ~CondNode();

  virtual void acceptVisitor(ABSASTVisitor* visitor);
};
