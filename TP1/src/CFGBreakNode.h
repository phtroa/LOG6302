#pragma once

#include "CFGTreeNode.h"

class CFGBreakNode : public CFGTreeNode
{
  public:
    CFGBreakNode(int begin, int end);
    ~CFGBreakNode();
    bool isLinkNeeded() const;

    void acceptVisitor(CFGTreeVisitor* visitor);
};
