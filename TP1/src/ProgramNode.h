#pragma once

#include <string>

#include "ABSNode.h"

class ProgramNode : public ABSNode {
public:
  ProgramNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
