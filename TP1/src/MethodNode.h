#pragma once

#include "ABSNode.h"

class MethodNode : public ABSNode {
public:
  MethodNode(const std::string& myClassName, const std::string& myFname,
              int line, int visibility = 0);

  ~MethodNode();

  void setMethodName(const std::string& name);
  std::string getMethodName() const;

  void setFileName(const std::string& name);
  std::string getFileName() const;


  void setReturnType(const std::string& type);
  std::string getReturnType() const;

  void addArgType(const std::string& argType);
  std::vector<std::string>::iterator argsTypesBegin();
  std::vector<std::string>::iterator argsTypesEnd();

  int getVisibility() const;

  void acceptVisitor(ABSASTVisitor* visitor);

private:
  std::string methodName;
  std::string fileName;
  int methodVis;
  std::string returnType;
  std::vector<std::string> argsTypes;
};
