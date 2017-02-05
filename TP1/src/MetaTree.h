#pragma once

#include <map>
#include <memory>
#include <string>

#include "ABSNode.h"

class MetaTree {
public:
  bool isMethodIn(const std::string& className,const std::string& methodName);
  void addMethodIn(const std::string& className,const std::string& methodName);

  bool isClassIn(const std::string& className);
  void addPtrToClass(const std::string& className, std::shared_ptr<ABSNode> ptr);
  std::shared_ptr<ABSNode> getPtrToClass(const std::string& className);

private:
  std::map<std::string, std::shared_ptr<ABSNode> > classNameToPtr;
  std::map<std::string, bool> isClassMethodIn;
};
