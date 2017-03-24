#pragma once

#include "CFGTreeNode.h"

class CFGReturnNode : public CFGTreeNode
{
  public:
    CFGReturnNode(int begin, int end);
    ~CFGReturnNode();
    bool isLinkNeeded() const;

    void acceptVisitor(CFGTreeVisitor* visitor);
};
