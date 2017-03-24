#include "UMLAttribute.h"

UMLAttribute::UMLAttribute(const std::string& name, const std::string& type,
   int visibility) : attName(name), vis(visibility), attType(type)
{
}

std::string UMLAttribute::getAsString() const
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

  std::string res = visStr + " " + attName + " : " + attType + "\\l";
  return res;
}


std::string UMLAttribute::getName() const
{
  return attName;
}
