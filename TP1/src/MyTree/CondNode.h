#pragma once

#include "ABSNode.h"

class CondNode : public ABSNode {
public:
  CondNode(std::weak_ptr<ABSNode> parent);
};
