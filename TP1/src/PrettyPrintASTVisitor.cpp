#include "PrettyPrintASTVisitor.h"

#include <iomanip>

#include "ClassNode.h"
#include "IfNode.h"
#include "JumpNode.h"
#include "ForNode.h"
#include "WhileNode.h"
#include "DoWhileNode.h"
#include "MethodNode.h"
#include "NamespaceNode.h"
#include "ProgramNode.h"
#include "ReturnNode.h"
#include "BlockNode.h"
#include "VarNode.h"
#include "AttributeNode.h"
#include "AssignNode.h"


PrettyPrintASTVisitor::PrettyPrintASTVisitor(std::ostream& stream) : spacePadding(0), o(stream)
{
}

PrettyPrintASTVisitor::~PrettyPrintASTVisitor()
{
}


  void PrettyPrintASTVisitor::writeSpaces(int nb)
  {
    for (int i = 0; i < nb; i++) {
      o << " ";
    }
  }

 void PrettyPrintASTVisitor::visitPre(ClassNode* node)
{

  writeSpaces(spacePadding);
  o << "+";
  o << "ClassNode : " << node->getClassName() << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(IfNode* node)
{

  writeSpaces(spacePadding);
  o << "+";
  o << "IfNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(SwitchNode* node)
{

  writeSpaces(spacePadding);
  o << "+";
  o << "SwitchNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(BreakNode* node)
{
  writeSpaces(spacePadding);
  o << "+";
  o << "BreakNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(ContinueNode* node)
{
  writeSpaces(spacePadding);
  o << "+";
  o << "ContinueNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(ForNode* node)
{
  writeSpaces(spacePadding);
  o << "+";
  o << "ForNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(WhileNode* node)
{
  writeSpaces(spacePadding);
  o << "+";
  o << "WhileNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(DoWhileNode* node)
{
  writeSpaces(spacePadding);
  o << "+";
  o << "DoWhileNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(MethodNode* node)
{
  writeSpaces(spacePadding);
  o << "+";
  o << "MethodNode : " << node->getMethodName() << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(NamespaceNode* node)
{
  writeSpaces(spacePadding);
  o << "+";
  o << "NamespaceNode : " << node->getName() << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(ProgramNode* node)
{
  writeSpaces(spacePadding);
  o << "+";
  o << "ProgramNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(VarNode* node)
{
  writeSpaces(spacePadding);
  o << "+";
  o << "VarNode : " << node->getVarName() << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(AttributeNode* node)
{
  writeSpaces(spacePadding);
  o << "+";
  o << "AttNode : " << node->getAttName() << node->getType().getType() << std::endl;
  spacePadding++;
}

void PrettyPrintASTVisitor::visitPre(AssignNode* node)
{
  writeSpaces(spacePadding);
  o << "+";
  o << "AssignNode : " << node->getVarName() << std::endl;
  spacePadding++;

}

 void PrettyPrintASTVisitor::visitPre(ReturnNode* node)
{
  writeSpaces(spacePadding);
  o << "+";
  o << "ReturnNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPre(BlockNode* node)
{
  writeSpaces(spacePadding);
  o << "+";
  o << "BlockNode" << std::endl;
  spacePadding++;
}

 void PrettyPrintASTVisitor::visitPost(ClassNode* node)
{
  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(IfNode* node)
{
  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(SwitchNode* node)
{
  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(BreakNode* node)
{
  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(ContinueNode* node)
{
  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(WhileNode* node)
{
  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(DoWhileNode* node)
{
  spacePadding--;
}

 void PrettyPrintASTVisitor::visitPost(ForNode* node)
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

 void PrettyPrintASTVisitor::visitPost(AssignNode* node)
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
