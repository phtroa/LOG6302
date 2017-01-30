#include "MetricASTVisitor.h"

#include "ClassNode.h"
#include "CondNode.h"
#include "JumpNode.h"
#include "LoopNode.h"
#include "MethodNode.h"
#include "ProgramNode.h"
#include "VarNode.h"


MetricASTVisitor::MetricASTVisitor() : currId(0), nbIf(0), nbLoop(0),
 nbJump(0), nbVar(0)
{
}

 void MetricASTVisitor::visitPre(ClassNode* node)
{
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

 void MetricASTVisitor::visitPre(ProgramNode* node)
{
   std::cout << "Id,file's name, class' name, method's name,#cond,#loop,#Jump,#Variables" << std::endl;
}

 void MetricASTVisitor::visitPre(VarNode* node)
{
  nbVar++;
}

 void MetricASTVisitor::visitPost(ClassNode* node)
{
  className = "Should never be seen, problem in visitor";
  fileName = "Should never be seen, problem in visitor";
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
    std::cout << currId << "," << fileName << "," << className << ","
    << node->getMethodName() << "," << nbIf << "," << nbLoop << ","
    << nbJump << "," << nbVar << std::endl;
}

 void MetricASTVisitor::visitPost(ProgramNode* node)
{
}

 void MetricASTVisitor::visitPost(VarNode* node)
{
}
