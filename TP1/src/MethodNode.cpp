#include "MethodNode.h"

#include "ABSASTVisitor.h"

MethodNode::MethodNode(const std::string& myClassName, const std::string& myfName,
                        int line, int visibility)
: ABSNode(line), methodName(myClassName), fileName(myfName), methodVis(visibility)
{
}

MethodNode::~MethodNode()
{
}

void MethodNode::setMethodName(const std::string& name)
{
  methodName = name;
}

std::string MethodNode::getMethodName() const
{
  return methodName;
}

void MethodNode::setFileName(const std::string& name)
{
  fileName = name;
}

std::string MethodNode::getFileName() const
{
  return fileName;
}

void MethodNode::setReturnType(const std::string& type)
{
  returnType = type;
}

std::string MethodNode::getReturnType() const
{
  return returnType;
}

void MethodNode::addArgType(const std::string& argType)
{
  argsTypes.push_back(argType);
}

std::vector<std::string>::iterator MethodNode::argsTypesBegin()
{
  return argsTypes.begin();
}

std::vector<std::string>::iterator MethodNode::argsTypesEnd()
{
  return argsTypes.end();
}

int MethodNode::getVisibility() const {
  return methodVis;
}

void MethodNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
    visitor->visitBetween(this);
  }
  visitor->visitPost(this);
}
