#pragma once

#include "ABSNode.h"

class VarNode : public ABSNode {
public:
    VarNode(std::weak_ptr<ABSNode> parent);
};
