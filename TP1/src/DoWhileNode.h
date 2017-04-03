#pragma once

#include "LoopNode.h"

#include "ABSASTVisitor.h"

class DoWhileNode : public LoopNode {
public:
  DoWhileNode(int line);
  ~DoWhileNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
