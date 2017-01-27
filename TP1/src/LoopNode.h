#pragma once

#include "ABSNode.h"

class LoopNode : public ABSNode {
public:
  LoopNode(std::weak_ptr<ABSNode> parent);
};
