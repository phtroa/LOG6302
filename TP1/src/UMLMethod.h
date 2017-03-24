#pragma once

#include <string>
#include <vector>

class UMLMethod
{
public:
  UMLMethod(const std::string& name, const std::string& returnType,
     std::vector<std::string> argsTypes, int visibility);
     std::string getAsString();
private:
  std::string methodName;
  std::string rtType;
  std::vector<std::string> agTypes;
  int vis;
};
