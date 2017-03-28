#include "ABSASTVisitor.h"

ABSASTVisitor::~ABSASTVisitor()
{
}

////////////////// PRE ///////////////////////
 void ABSASTVisitor::visitPre(ClassNode* node)
{
}

 void ABSASTVisitor::visitPre(ABSNode* node)
{
}

 void ABSASTVisitor::visitPre(CondNode* node)
{
}

void ABSASTVisitor::visitPre(BreakNode* node)
{
}

void ABSASTVisitor::visitPre(ContinueNode* node)
{
}

 void ABSASTVisitor::visitPre(LoopNode* node)
{
}

 void ABSASTVisitor::visitPre(MethodNode* node)
{
}

 void ABSASTVisitor::visitPre(NamespaceNode* node)
{
}

 void ABSASTVisitor::visitPre(ProgramNode* node)
{
}

 void ABSASTVisitor::visitPre(VarNode* node)
{
}

 void ABSASTVisitor::visitPre(AttributeNode* node)
{
}

 void ABSASTVisitor::visitPre(AssignNode* node)
{
}

 void ABSASTVisitor::visitPre(ReturnNode* node)
{
}

 void ABSASTVisitor::visitPre(BlockNode* node)
{
}

/////////////// BETWEEN /////////////////////

void ABSASTVisitor::visitBetween(ClassNode* node)
{
}

void ABSASTVisitor::visitBetween(ABSNode* node)
{
}

void ABSASTVisitor::visitBetween(CondNode* node)
{
}

void ABSASTVisitor::visitBetween(BreakNode* node)
{
}

void ABSASTVisitor::visitBetween(ContinueNode* node)
{
}

void ABSASTVisitor::visitBetween(LoopNode* node)
{
}

void ABSASTVisitor::visitBetween(MethodNode* node)
{
}

void ABSASTVisitor::visitBetween(NamespaceNode* node)
{
}

void ABSASTVisitor::visitBetween(ProgramNode* node)
{
}

void ABSASTVisitor::visitBetween(VarNode* node)
{
}

void ABSASTVisitor::visitBetween(AttributeNode* node)
{
}

void ABSASTVisitor::visitBetween(AssignNode* node)
{
}

void ABSASTVisitor::visitBetween(ReturnNode* node)
{
}

void ABSASTVisitor::visitBetween(BlockNode* node)
{
}
//////////////// POST ///////////////////////
 void ABSASTVisitor::visitPost(ClassNode* node)
{
}

 void ABSASTVisitor::visitPost(ABSNode* node)
{
}

 void ABSASTVisitor::visitPost(CondNode* node)
{
}

 void ABSASTVisitor::visitPost(LoopNode* node)
{
}

 void ABSASTVisitor::visitPost(MethodNode* node)
{
}

 void ABSASTVisitor::visitPost(NamespaceNode* node)
{
}

 void ABSASTVisitor::visitPost(ProgramNode* node)
{
}

 void ABSASTVisitor::visitPost(VarNode* node)
{
}

 void ABSASTVisitor::visitPost(AttributeNode* node)
{
}

 void ABSASTVisitor::visitPost(AssignNode* node)
{
}

void ABSASTVisitor::visitPost(BreakNode* node)
{
}

void ABSASTVisitor::visitPost(ContinueNode* node)
{
}

 void ABSASTVisitor::visitPost(ReturnNode* node)
{
}

 void ABSASTVisitor::visitPost(BlockNode* node)
{
}
