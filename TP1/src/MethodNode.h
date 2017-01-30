#pragma once

#include "ABSNode.h"

class MethodNode : public ABSNode {
public:
  MethodNode(const std::string& name);
  void setMethodName(const std::string& name);
  std::string getMethodName() const;

  void acceptVisitor(ABSASTVisitor* visitor);
private:
  std::string methodName;
};
