#pragma once

#include <string>

#include "ABSNode.h"

class ProgramNode : public ABSNode {
public:
  ProgramNode();

  virtual void incrCond();
  virtual void incrLoop();
  virtual void incrJump();
  virtual void incrVar();

private:
  ProgramNode(std::weak_ptr<ABSNode> parent);
};
