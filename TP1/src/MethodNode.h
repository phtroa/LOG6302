#pragma once

#include "ABSNode.h"

class MethodNode : public ABSNode {
public:
  MethodNode(const std::string& myClassName, const std::string& myFname);
  void setMethodName(const std::string& name);
  std::string getMethodName() const;
  void setFileName(const std::string& name);
  std::string getFileName() const;

  void acceptVisitor(ABSASTVisitor* visitor);
private:
  std::string methodName;
  std::string fileName;
};
