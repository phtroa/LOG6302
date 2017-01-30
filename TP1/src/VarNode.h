#pragma once

#include "ABSNode.h"

class VarNode : public ABSNode {
public:
    VarNode();

    void acceptVisitor(ABSASTVisitor* visitor);
};
