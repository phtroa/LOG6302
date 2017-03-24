#pragma once

#include <vector>
#include <memory>

class CFGTreeVisitor;

class CFGTreeNode
{
  public:
    CFGTreeNode(int begin, int end);
    virtual ~CFGTreeNode() = 0;
    virtual int getBeginID() const;
    virtual int getEndID() const;
    virtual bool isLinkNeeded() const;
    std::shared_ptr<CFGTreeNode> getNode(int i) const;
    void addChild(std::shared_ptr<CFGTreeNode> child);
    void setParent(std::weak_ptr<CFGTreeNode> parent);
    int getNbChildren() const;
    std::shared_ptr<CFGTreeNode> getParent() const;

    virtual void acceptVisitor(CFGTreeVisitor* visitor) = 0;
  private:
    int beginID;
    int endId;
    std::vector<std::shared_ptr<CFGTreeNode>> children;
    std::weak_ptr<CFGTreeNode> parent;
};
