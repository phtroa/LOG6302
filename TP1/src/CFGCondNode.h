#pragma once

#include "CFGTreeNode.h"

class CFGCondNode : public CFGTreeNode
{
  public:
    CFGCondNode(int begin, int end, int cond);
    ~CFGCondNode();

    void acceptVisitor(CFGTreeVisitor* visitor);
    int getCondID() const;
  private:
    int condID;
};
