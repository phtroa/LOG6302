#pragma once

#include "ABSNode.h"

class ClassNode : public ABSNode {
public:
  ClassNode(const std::string& name, std::weak_ptr<ABSNode> parent);
  void setClassName(const std::string& name);
  std::string getClassName() const;

private:
  std::string className;
};
