#pragma once

#include "LoopNode.h"

class ForNode : public LoopNode {
public:
  ForNode(int line);
  ~ForNode();
};
