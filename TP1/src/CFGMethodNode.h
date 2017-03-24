#pragma once

#include "CFGTreeNode.h"

class CFGMethodNode : public CFGTreeNode
{
  public:
    CFGMethodNode(int begin, int end);
    ~CFGMethodNode();

    void acceptVisitor(CFGTreeVisitor* visitor);
};
