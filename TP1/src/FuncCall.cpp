#include "FuncCall.h"

#include "ABSASTVisitor.h"

FuncCall::FuncCall(const std::string& myFname, int line) : ABSNode(line), funcName(myFname)
{
}

FuncCall::~FuncCall()
{
}

void FuncCall::setFuncName(const std::string& name)
{
  funcName = name;
}

std::string FuncCall::getFuncName() const
{
  return funcName;
}

void FuncCall::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
    visitor->visitBetween(this);
  }
  visitor->visitPost(this);
}
