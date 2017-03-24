#pragma once

#include <ostream>
#include <vector>
#include <string>

#include "UMLAttribute.h"
#include "UMLMethod.h"

class UMLClass {
public:
  UMLClass (const std::string& className, const std::string& classID);

  void addPublicAttribute(const UMLAttribute& attribute);
  void addProtectedAttribute(const UMLAttribute& attribute);
  void addPrivateAttribute(const UMLAttribute& attribute);

  void addPublicMethod(const UMLMethod& method);
  void addProtectedMethod(const UMLMethod& method);
  void addPrivateMethod(const UMLMethod& method);

  void dump(std::ostream& o);

  std::string getName() const;
  std::string getID() const;

private:
    std::string name;
    std::string id;

    std::vector<UMLAttribute> publicAttr;
    std::vector<UMLAttribute> protectedAttr;
    std::vector<UMLAttribute> privateAttr;

    std::vector<UMLMethod> publicMeth;
    std::vector<UMLMethod> protectedMeth;
    std::vector<UMLMethod> privateMeth;
};
