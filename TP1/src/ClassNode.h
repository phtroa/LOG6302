#pragma once

#include "ABSNode.h"

class ClassNode : public ABSNode {
public:
  ClassNode(const std::string& name, const std::string& file);
  void setClassName(const std::string& name);
  std::string getClassName() const;
  void setFilePath(const std::string& name);
  std::string getFilePath() const;

  void acceptVisitor(ABSASTVisitor* visitor);

private:
  std::string className;
  std::string filePath;
};
