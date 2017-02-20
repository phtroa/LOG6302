#include "MetaTree.h"

bool MetaTree::isMethodIn(const std::string& className,
   const std::string& methodId)
{
  std::string id = className + methodId;

  return isClassMethodIn.count(id) > 0;
}

std::shared_ptr<ABSNode> MetaTree::getPtrToClass(const std::string& className)
{
  return classNameToPtr[className];
}

std::shared_ptr<ABSNode> MetaTree::getPtrToNamespace(const std::string& namespaceID)
{
  return NamespaceToPtr[namespaceID];
}

bool MetaTree::isClassIn(const std::string& className) const
{
  return classNameToPtr.count(className) > 0;
}


void MetaTree::initializedClass(const std::string& className, bool isInitialised)
{
  isClassInitialized[className] = isInitialised;
}

bool MetaTree::isInitialised(const std::string& className) 
{
  return isClassInitialized.count(className) > 0 && isClassInitialized[className];
}

bool MetaTree::isNamespaceIn(const std::string& namespaceID)
{
  return NamespaceToPtr.count(namespaceID) > 0;
}

void MetaTree::addPtrToClass(const std::string& className,
   std::shared_ptr<ABSNode> ptr)
{
  classNameToPtr[className] = ptr;
}

void MetaTree::addPtrToNamespace(const std::string& namespaceID,
   std::shared_ptr<ABSNode> ptr)
{
  NamespaceToPtr[namespaceID] = ptr;
}

void MetaTree::addMethodIn(const std::string& className,
  const std::string& methodId)
{
  std::string id = className + methodId;

  isClassMethodIn[id] = true;
}

void MetaTree::addAttributIn(const std::string& className,
  const std::string& attributId)
{
  std::string id = className + attributId;

  isClassAttributeIn[id] = true;
}

bool MetaTree::isAttributIn(const std::string& className,
   const std::string& attributId)
{
  std::string id = className + attributId;

  return isClassAttributeIn.count(id) > 0;
}
