#pragma once

#include "ABSNode.h"

class ReturnNode : public ABSNode {
public:
  ReturnNode();
  ~ReturnNode();
  void acceptVisitor(ABSASTVisitor* visitor);
};
