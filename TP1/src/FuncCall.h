#pragma once

#include <string>

#include "ABSNode.h"

class  FuncCall : public ABSNode
{
public:
  FuncCall(const std::string& myFname, int line);
  ~FuncCall();

  void setFuncName(const std::string& name);
  std::string getFuncName() const;

  void acceptVisitor(ABSASTVisitor* visitor);
private:
  std::string funcName;
};
