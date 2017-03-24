#pragma once

#include <vector>
#include <string>

#include "ABSASTVisitor.h"

#include "UMLBuilder.h"
#include "UMLClass.h"
#include "UMLAttribute.h"
#include "UMLMethod.h"
#include "InheritanceRel.h"
#include "CompositionRel.h"

//Create UML diagram
class UMLASTVisitor : public ABSASTVisitor {
public:
  UMLASTVisitor();
  ~UMLASTVisitor();
    virtual void visitPre(ClassNode* node);
    virtual void visitPre(MethodNode* node);
    virtual void visitPre(AttributeNode* node);

    virtual void visitPost(ClassNode* node);
    virtual void visitPost(ProgramNode* node);

private:
  std::vector<UMLClass> classStack;
  UMLBuilder builder;
  void replaceAll( std::string &s, const std::string &search,
                                    const std::string &replace ) const;
  void cleanupString(std::string& myStr) const;
};
