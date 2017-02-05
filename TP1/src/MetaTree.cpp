#include "MetaTree.h"

bool MetaTree::isMethodIn(const std::string& className,
   const std::string& methodName)
{
  std::string id = className + methodName;

  return isClassMethodIn.count(id) > 0;
}

std::shared_ptr<ABSNode> MetaTree::getPtrToClass(const std::string& className)
{
  return classNameToPtr[className];
}

bool MetaTree::isClassIn(const std::string& className)
{
  return classNameToPtr.count(className) > 0;
}

void MetaTree::addPtrToClass(const std::string& className,
   std::shared_ptr<ABSNode> ptr)
{
  classNameToPtr[className] = ptr;
}


void MetaTree::addMethodIn(const std::string& className,
  const std::string& methodName)
{
  std::string id = className + methodName;

  isClassMethodIn[id] = true;
}
