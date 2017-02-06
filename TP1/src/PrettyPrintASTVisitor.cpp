#include "PrettyPrintASTVisitor.h"

#include <iomanip>

#include "ClassNode.h"
#include "CondNode.h"
#include "JumpNode.h"
#include "LoopNode.h"
#include "MethodNode.h"
#include "ProgramNode.h"
#include "VarNode.h"


PrettyPrintASTVisitor::PrettyPrintASTVisitor() : spacePadding(0)
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

 void PrettyPrintASTVisitor::visitPost(ProgramNode* node)
{

  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(VarNode* node)
{

  spacePadding--;
}
