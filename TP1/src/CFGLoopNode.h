#pragma once

#include "CFGTreeNode.h"

class CFGLoopNode : public CFGTreeNode
{
  public:
    CFGLoopNode(int begin, int end, int condid);
    ~CFGLoopNode();

    void acceptVisitor(CFGTreeVisitor* visitor);
    int getCondID() const;
  private:
    int condID;
};
