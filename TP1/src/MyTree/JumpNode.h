#pragma once

#include "ABSNode.h"

class JumpNode : public ABSNode {
public:
  JumpNode(std::weak_ptr<ABSNode> parent);
};
