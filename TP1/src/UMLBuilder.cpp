#include "UMLBuilder.h"

UMLBuilder::UMLBuilder(const std::string& diagramName,
  const std::string& fontName,
  int fontSize, const std::string& shape)
  : name(diagramName), fName(fontName), fSize(fontSize), nodeShape(shape)
{
}

void UMLBuilder::addClass(const UMLClass& UClass)
{
  classes.push_back(UClass);
}

void UMLBuilder::addComposition(const std::string& current,
                                const std::string& attr)
{
  cRelation.link(current, attr);
}

void UMLBuilder::addInheritance(const std::string& derived,
                                const std::string& base)
{
  IRelation.link(derived, base);
}

void UMLBuilder::dump(std::ostream& o)
{
  o << "digraph " << name << "{" << std::endl;
  o << "fontname = " << fName << std::endl;
  o << "fontsize = " << fSize << std::endl;
  o << "node [" << std::endl;
  o << "fontname = " << fName << std::endl;
  o << "fontsize = " << fSize << std::endl;
  o << "shape = " << nodeShape << std::endl;
  o << "]" << std::endl;

  for (auto it = classes.begin(); it != classes.end(); it++) {
    it->dump(o);
  }
  cRelation.dump(o);
  IRelation.dump(o);

  o << "}" << std::endl;
}
