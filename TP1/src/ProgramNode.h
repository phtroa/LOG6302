#pragma once

#include <string>

#include "ABSNode.h"

//Symbolized te root of the tree
class ProgramNode : public ABSNode {
public:
  ProgramNode();

  void acceptVisitor(ABSASTVisitor* visitor);
};
