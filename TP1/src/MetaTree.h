#pragma once

#include <map>
#include <memory>
#include <string>

#include "ABSNode.h"

//This class collects all the information about where to find a class in the
//tree. It also keep track of which methods have been inserted in the tree.
class MetaTree {
public:
  //tests if the method has already been added
  bool isMethodIn(const std::string& className, const std::string& methodId);
  //adds the method
  void addAttributIn(const std::string& className, const std::string& methodId);
  //tests if the method has already been added
  bool isAttributIn(const std::string& className, const std::string& attributId);
  //adds the method
  void addMethodIn(const std::string& className, const std::string& methodId);
  //namespace
  bool isNamespaceIn(const std::string& namespaceID);

  void initializedClass(const std::string& className, bool isInitialised);

  //tests if the class has been added
  bool isClassIn(const std::string& className) const;
  bool isInitialised(const std::string& className);
  //add a class to our index
  void addPtrToClass(const std::string& className, std::shared_ptr<ABSNode> ptr);
  void addPtrToNamespace(const std::string& namespaceID, std::shared_ptr<ABSNode> ptr);
  //get a class
  std::shared_ptr<ABSNode> getPtrToClass(const std::string& className);
  std::shared_ptr<ABSNode> getPtrToNamespace(const std::string& namespaceID);

private:
  std::map<std::string, std::shared_ptr<ABSNode> > classNameToPtr;
  std::map<std::string, std::shared_ptr<ABSNode> > NamespaceToPtr;
  std::map<std::string, bool> isClassMethodIn;
  std::map<std::string, bool> isClassAttributeIn;
  std::map<std::string, bool> isClassInitialized;
};
