#include "MetricASTVisitor.h"

#include "ClassNode.h"
#include "CondNode.h"
#include "JumpNode.h"
#include "LoopNode.h"
#include "MethodNode.h"
#include "NamespaceNode.h"
#include "ProgramNode.h"
#include "VarNode.h"


MetricASTVisitor::MetricASTVisitor() : currId(0), nbIf(0), nbLoop(0),
 nbJump(0), nbVar(0)
{
  std::cout << "id,nom Fichier,nom Classe, nom méthode, #cond, #boucle, #jump, #var" << std::endl;
}

 void MetricASTVisitor::visitPre(ClassNode* node)
{
  //saving names in case of class declaration inside another class
  oldClassName = className;
  oldFileName = fileName;

  //settting current names
  className = node->getClassName();
  fileName = node->getFilePath();
}

 void MetricASTVisitor::visitPre(CondNode* node)
{
  nbIf++;
}

 void MetricASTVisitor::visitPre(JumpNode* node)
{
  nbJump++;
}

 void MetricASTVisitor::visitPre(LoopNode* node)
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

 void MetricASTVisitor::visitPre(NamespaceNode* node)
{
}

 void MetricASTVisitor::visitPre(ProgramNode* node)
{
}

 void MetricASTVisitor::visitPre(VarNode* node)
{
  nbVar++;
}

 void MetricASTVisitor::visitPre(AttributeNode* node)
{
}

 void MetricASTVisitor::visitPost(ClassNode* node)
{
  className = oldClassName;
  fileName = oldFileName;
}

 void MetricASTVisitor::visitPost(CondNode* node)
{
}

 void MetricASTVisitor::visitPost(JumpNode* node)
{
}

 void MetricASTVisitor::visitPost(LoopNode* node)
{
}

 void MetricASTVisitor::visitPost(MethodNode* node)
{
    std::cout << currId << "," << node->getFileName() << "," << className << ","
    << node->getMethodName() << "," << nbIf << "," << nbLoop << ","
    << nbJump << "," << nbVar << std::endl;
    currId++;
}

 void MetricASTVisitor::visitPost(NamespaceNode* node)
{
}

 void MetricASTVisitor::visitPost(ProgramNode* node)
{
}

 void MetricASTVisitor::visitPost(VarNode* node)
{
}

 void MetricASTVisitor::visitPost(AttributeNode* node)
{
}
