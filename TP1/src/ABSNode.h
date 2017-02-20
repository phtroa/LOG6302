#pragma once

#include <vector>
#include <memory>
#include <string>

class ABSASTVisitor;

//represent a node in our ast
class ABSNode {
public:
  ABSNode();
  ABSNode(std::shared_ptr<ABSNode> parent);
  void addChild(std::shared_ptr<ABSNode> child);
  void setParent(std::weak_ptr<ABSNode> parent);
  std::shared_ptr<ABSNode> getParent() const;

  virtual void acceptVisitor(ABSASTVisitor* visitor) = 0;

protected:
  std::vector<std::shared_ptr<ABSNode>> children;
  std::weak_ptr<ABSNode> parent;
};
