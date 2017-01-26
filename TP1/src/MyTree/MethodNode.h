#pragma once

#include "ABSNode.h"

class MethodNode : public ABSNode {
public:
  MethodNode(std::weak_ptr<ABSNode> parent);

  virtual void incrCond();
  virtual void incrLoop();
  virtual void incrJump();
  virtual void incrVar();
private:
  int nbCond;
  int nbLoop;
  int nbJump;
  int nbVar;
};
