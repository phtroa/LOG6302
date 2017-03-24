#include "UMLMethod.h"


UMLMethod::UMLMethod(const std::string& name, const std::string& returnType,
   std::vector<std::string> argsTypes, int visibility)
   : methodName(name), rtType(returnType), agTypes(argsTypes), vis(visibility)
{
}

std::string UMLMethod::getAsString()
{
  std::string visStr;
  switch (vis) {
    case 0:
      visStr = "+";
      break;
    case 1:
      visStr = "#";
      break;
    case 2:
      visStr = "-";
      break;
    case 3:
      visStr = "none";
      break;
  }

  std::string res = visStr + " " + methodName +"(";
  bool isFirst = true;
  for (auto it = agTypes.begin(); it != agTypes.end(); it++) {
    if (isFirst) {
      res += *it;
      isFirst = false;
    }
    else {
      res += "," + *it;
    }
  }
  res += ") : " + rtType + "\\l";

  return res;
}
