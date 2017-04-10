#include "MetricASTVisitor.h"

#include "ClassNode.h"
#include "IfNode.h"
#include "BreakNode.h"
#include "ContinueNode.h"
#include "ForNode.h"
#include "WhileNode.h"
#include "DoWhileNode.h"
#include "MethodNode.h"
#include "NamespaceNode.h"
#include "ProgramNode.h"
#include "ReturnNode.h"
#include "BlockNode.h"
#include "VarNode.h"


MetricASTVisitor::MetricASTVisitor(std::ostream& stream) : currId(0), nbIf(0), nbLoop(0),
 nbJump(0), nbVar(0), o(stream)
{
  o << "id,nom Fichier,nom Classe, nom méthode, #cond, #boucle, #jump, #var" << std::endl;
}

MetricASTVisitor::~MetricASTVisitor()
{
}

 void MetricASTVisitor::visitPre(ClassNode* node)
{
  //saving names in case of class declaration inside another class
  oldClassName = className;
  oldFileName = fileName;

  //setting current names
  className = node->getClassName();
  fileName = node->getFilePath();
}

 void MetricASTVisitor::visitPre(IfNode* node)
{
  nbIf++;
}

 void MetricASTVisitor::visitPre(SwitchNode* node)
{
  nbIf++;
}

 void MetricASTVisitor::visitPre(BreakNode* node)
{
  nbJump++;
}

 void MetricASTVisitor::visitPre(ContinueNode* node)
{
  nbJump++;
}

 void MetricASTVisitor::visitPre(ForNode* node)
{
  nbLoop++;
}

 void MetricASTVisitor::visitPre(WhileNode* node)
{
  nbLoop++;
}

 void MetricASTVisitor::visitPre(DoWhileNode* node)
{
  nbLoop++;
}

 void MetricASTVisitor::visitPre(MethodNode* node)
{
  nbIf = 0;
  nbLoop = 0;
  nbJump = 0;
  nbVar = 0;
}

 void MetricASTVisitor::visitPre(VarNode* node)
{
  nbVar++;
}

 void MetricASTVisitor::visitPost(ClassNode* node)
{
  className = oldClassName;
  fileName = oldFileName;
}

 void MetricASTVisitor::visitPost(MethodNode* node)
{
    o << currId << "," << node->getFileName() << "," << className << ","
    << node->getMethodName() << "," << nbIf << "," << nbLoop << ","
    << nbJump << "," << nbVar << std::endl;
    currId++;
}
