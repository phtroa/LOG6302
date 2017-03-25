#pragma once

#include "LoopNode.h"

#include "ABSASTVisitor.h"

class WhileNode : public LoopNode {
public:
  WhileNode(int line);
  ~WhileNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
