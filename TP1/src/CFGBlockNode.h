#include "CFGTreeNode.h"

class CFGBlockNode : public CFGTreeNode
{
  public:
    CFGBlockNode();
    ~CFGBlockNode();

    virtual int getBeginID() const;
    virtual int getEndID() const;
    virtual bool isLinkNeeded() const;

    void acceptVisitor(CFGTreeVisitor* visitor);
};
