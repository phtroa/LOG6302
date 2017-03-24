#include "PrettyPrintASTVisitor.h"

#include <iomanip>

#include "ClassNode.h"
#include "CondNode.h"
#include "JumpNode.h"
#include "LoopNode.h"
#include "MethodNode.h"
#include "NamespaceNode.h"
#include "ProgramNode.h"
#include "ReturnNode.h"
#include "BlockNode.h"
#include "VarNode.h"
#include "AttributeNode.h"


PrettyPrintASTVisitor::PrettyPrintASTVisitor() : spacePadding(0)
{
}

PrettyPrintASTVisitor::~PrettyPrintASTVisitor()
{
}


  void PrettyPrintASTVisitor::writeSpaces(int nb)
  {
    for (int i = 0; i < nb; i++) {
      std::cout << " ";
    }
  }

 void PrettyPrintASTVisitor::visitPre(ClassNode* node)
{

  writeSpaces(spacePadding);
  std::cout << "+";
  std::cout << "ClassNode : " << node->getClassName() << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(CondNode* node)
{

  writeSpaces(spacePadding);
  std::cout << "+";
  std::cout << "CondNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(JumpNode* node)
{

  writeSpaces(spacePadding);
  std::cout << "+";
  std::cout << "JumpNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(LoopNode* node)
{

  writeSpaces(spacePadding);
  std::cout << "+";
  std::cout << "LoopNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(MethodNode* node)
{

  writeSpaces(spacePadding);
  std::cout << "+";
  std::cout << "MethodNode : " << node->getMethodName() << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(NamespaceNode* node)
{
  writeSpaces(spacePadding);
  std::cout << "+";
  std::cout << "NamespaceNode : " << node->getName() << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(ProgramNode* node)
{

  writeSpaces(spacePadding);
  std::cout << "+";
  std::cout << "ProgramNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(VarNode* node)
{

  writeSpaces(spacePadding);
  std::cout << "+";
  std::cout << "VarNode : " << node->getVarName() << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(AttributeNode* node)
{

  writeSpaces(spacePadding);
  std::cout << "+";
  std::cout << "AttNode : " << node->getAttName() << node->getType().getType() << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(ReturnNode* node)
{

  writeSpaces(spacePadding);
  std::cout << "+";
  std::cout << "ReturnNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(BlockNode* node)
{

  writeSpaces(spacePadding);
  std::cout << "+";
  std::cout << "BlockNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPost(ClassNode* node)
{

  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(CondNode* node)
{

  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(JumpNode* node)
{

  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(LoopNode* node)
{

  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(MethodNode* node)
{

  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(NamespaceNode* node)
{

  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(ProgramNode* node)
{

  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(VarNode* node)
{

  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(AttributeNode* node)
{
  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(ReturnNode* node)
{
  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(BlockNode* node)
{
  spacePadding--;
}
