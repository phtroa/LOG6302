#include "UMLASTVisitor.h"

#include "ClassNode.h"
#include "CondNode.h"
#include "JumpNode.h"
#include "LoopNode.h"
#include "MethodNode.h"
#include "NamespaceNode.h"
#include "ProgramNode.h"
#include "ReturnNode.h"
#include "VarNode.h"
#include "AttributeNode.h"

UMLASTVisitor::UMLASTVisitor() : ABSASTVisitor(), builder("test")
{
}

UMLASTVisitor::~UMLASTVisitor()
{
}

//from http://stackoverflow.com/questions/4643512/replace-substring-with-another-substring-c
void UMLASTVisitor::replaceAll( std::string &s,
                                const std::string &search,
                                const std::string &replace ) const
{
    for( size_t pos = 0; ; pos += replace.length() ) {
        // Locate the substring to replace
        pos = s.find( search, pos );
        if( pos == std::string::npos ) break;
        // Replace by erasing and inserting
        s.erase( pos, search.length() );
        s.insert( pos, replace );
    }
}

void UMLASTVisitor::cleanupString(std::string& myStr) const
{
  replaceAll(myStr, "<", "\\<");
  replaceAll(myStr, ">", "\\>");
}

 void UMLASTVisitor::visitPre(ClassNode* node)
{
  UMLClass UClass(node->getClassName(), node->getID());
  classStack.push_back(UClass);
  for (auto it = node->baseBegin(); it != node->baseEnd(); it++) {
    builder.addInheritance(node->getID(), *it);
  }
}

 void UMLASTVisitor::visitPre(MethodNode* node)
{
  std::vector<std::string> argsTypes;
  for (auto it = node->argsTypesBegin(); it != node->argsTypesEnd(); it++) {
    std::string argType = *it;
    cleanupString(argType);
    argsTypes.push_back(argType);
  }
  std::string retType = node->getReturnType();
  cleanupString(retType);
  std::string methodName = node->getMethodName(); //in case we encounter operator<< or equivalent
  cleanupString(methodName);
  UMLMethod UMethod(methodName,
                    retType,
                    argsTypes,
                    node->getVisibility()
 );
 switch (node->getVisibility()) {
   case 0:
     classStack.back().addPublicMethod(UMethod);
     break;
   case 1:
     classStack.back().addProtectedMethod(UMethod);
     break;
   case 2:
     classStack.back().addPrivateMethod(UMethod);
     break;
 }

}

 void UMLASTVisitor::visitPre(AttributeNode* node)
{
  InfoType ifType = node->getType();
  std::string safeTypeStr = ifType.getType();
  cleanupString(safeTypeStr);
  UMLAttribute mUMLAttribute(node->getAttName(),
                            safeTypeStr,
                            node->getVisibility()
                           );
  switch (node->getVisibility()) {
    case 0:
      classStack.back().addPublicAttribute(mUMLAttribute);
      break;
    case 1:
      classStack.back().addProtectedAttribute(mUMLAttribute);
      break;
    case 2:
      classStack.back().addPrivateAttribute(mUMLAttribute);
      break;
  }

  if (ifType.isRelatedToClassType()) {
    builder.addComposition(classStack.back().getID(), ifType.getRefClassId());
  }

}

 void UMLASTVisitor::visitPost(ClassNode* node)
{
  builder.addClass(classStack.back());
  classStack.pop_back();
}

 void UMLASTVisitor::visitPost(ProgramNode* node)
{
  builder.dump(std::cout);
}
