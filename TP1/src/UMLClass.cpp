#include "UMLClass.h"


UMLClass::UMLClass(const std::string& className, const std::string& classID) : name(className), id(classID)
{
}

void UMLClass::addPublicAttribute(const UMLAttribute& attribute)
{
  publicAttr.push_back(attribute);
}

void UMLClass::addProtectedAttribute(const UMLAttribute& attribute)
{
  protectedAttr.push_back(attribute);
}

void UMLClass::addPrivateAttribute(const UMLAttribute& attribute)
{
  privateAttr.push_back(attribute);
}

void UMLClass::addPublicMethod(const UMLMethod& method)
{
  publicMeth.push_back(method);
}

void UMLClass::addProtectedMethod(const UMLMethod& method)
{
  protectedMeth.push_back(method);
}

void UMLClass::addPrivateMethod(const UMLMethod& method)
{
  privateMeth.push_back(method);
}

std::string UMLClass::getName() const
{
  return name;
}

std::string UMLClass::getID() const
{
  return id;
}

void UMLClass::dump(std::ostream& o)
{
  o << id << " [" << std::endl;
  std::string res = "label = \"{" + name + "|";
  for (auto it = publicMeth.begin(); it != publicMeth.end(); it++) {
    res += it->getAsString();
  }
  for (auto it = protectedMeth.begin(); it != protectedMeth.end(); it++) {
    res += it->getAsString();
  }
  for (auto it = privateMeth.begin(); it != privateMeth.end(); it++) {
    res += it->getAsString();
  }

  res += "|";

  for (auto it = publicAttr.begin(); it != publicAttr.end(); it++) {
    res += it->getAsString();
  }
  for (auto it = protectedAttr.begin(); it != protectedAttr.end(); it++) {
    res += it->getAsString();
  }
  for (auto it = privateAttr.begin(); it != privateAttr.end(); it++) {
    res += it->getAsString();
  }
  res += "}\"";

  o << res << std::endl;
  o << "]" << std::endl;
}
