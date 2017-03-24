#pragma once

#include <vector>
#include <ostream>

#include "CompositionRel.h"
#include "InheritanceRel.h"
#include "UMLClass.h"

class UMLBuilder
{
  public:
    UMLBuilder(const std::string& diagramName,
      const std::string& fontName =  "\"Bitstream Vera Sans\"",
      int fontSize = 8, const std::string& shape = "\"record\"");
    void addClass(const UMLClass& UClass);

    void addComposition(const std::string& current, const std::string& attr);
    void addInheritance(const std::string& derived, const std::string& base);

    void dump(std::ostream& o);
  private:
    std::vector<UMLClass> classes;
    CompositionRel cRelation;
    InheritanceRel IRelation;

    std::string fName;
    int fSize;
    std::string nodeShape;
    std::string name;
};
