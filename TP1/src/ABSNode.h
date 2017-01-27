#pragma once

#include <vector>
#include <memory>
#include <string>

class ABSNode {
public:
  ABSNode(std::weak_ptr<ABSNode> parent) = 0;
  void addchild(std::shared_ptr<ABSNode> child);

  virtual void incrCond();
  virtual void incrLoop();
  virtual void incrJump();
  virtual void incrVar();

private:
  std::vector<std::shared_ptr<ABSNode>> children;
  std::weak_ptr<ABSNode> parent;
};
