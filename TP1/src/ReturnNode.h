#pragma once

#include "ABSNode.h"

class ReturnNode : public ABSNode {
public:
  ReturnNode(int line);
  ~ReturnNode();
  void acceptVisitor(ABSASTVisitor* visitor);
};
