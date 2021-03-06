#pragma once

#include <memory>

class ABSNode;
class AttributeNode;
class AssignNode;
class ClassNode;
class CaseNode;
class IfNode;
class SwitchNode;
class BlockNode;
class BreakNode;
class ContinueNode;
class WhileNode;
class DoWhileNode;
class ForNode;
class FuncCall;
class MethodNode;
class NamespaceNode;
class ProgramNode;
class ReturnNode;
class VarNode;

//Visitor pattern to visit a tree
//all the *Pre method are called before going into
//the children the *Post are called once all the chldren have been
//encoutered
//between method are called between two nodes
//beware that by default methods do nothing
//they must be implemented
class ABSASTVisitor {
public:
  virtual ~ABSASTVisitor() = 0;
  virtual void visitPre(ABSNode* node);
  virtual void visitPre(ClassNode* node);
  virtual void visitPre(CaseNode* node);
  virtual void visitPre(IfNode* node);
  virtual void visitPre(SwitchNode* node);
  virtual void visitPre(BreakNode* node);
  virtual void visitPre(ContinueNode* node);
  virtual void visitPre(WhileNode* node);
  virtual void visitPre(DoWhileNode* node);
  virtual void visitPre(ForNode* node);
  virtual void visitPre(FuncCall* node);
  virtual void visitPre(MethodNode* node);
  virtual void visitPre(ProgramNode* node);
  virtual void visitPre(VarNode* node);
  virtual void visitPre(AttributeNode* node);
  virtual void visitPre(AssignNode* node);
  virtual void visitPre(NamespaceNode* node);
  virtual void visitPre(ReturnNode* node);
  virtual void visitPre(BlockNode* node);

  virtual void visitBetween(ABSNode* node);
  virtual void visitBetween(ClassNode* node);
  virtual void visitBetween(CaseNode* node);
  virtual void visitBetween(IfNode* node);
  virtual void visitBetween(SwitchNode* node);
  virtual void visitBetween(BreakNode* node);
  virtual void visitBetween(ContinueNode* node);
  virtual void visitBetween(WhileNode* node);
  virtual void visitBetween(DoWhileNode* node);
  virtual void visitBetween(ForNode* node);
  virtual void visitBetween(FuncCall* node);
  virtual void visitBetween(MethodNode* node);
  virtual void visitBetween(ProgramNode* node);
  virtual void visitBetween(VarNode* node);
  virtual void visitBetween(AttributeNode* node);
  virtual void visitBetween(AssignNode* node);
  virtual void visitBetween(NamespaceNode* node);
  virtual void visitBetween(ReturnNode* node);
  virtual void visitBetween(BlockNode* node);

  virtual void visitPost(ABSNode* node);
  virtual void visitPost(ClassNode* node);
  virtual void visitPost(CaseNode* node);
  virtual void visitPost(IfNode* node);
  virtual void visitPost(SwitchNode* node);
  virtual void visitPost(BreakNode* node);
  virtual void visitPost(ContinueNode* node);
  virtual void visitPost(WhileNode* node);
  virtual void visitPost(DoWhileNode* node);
  virtual void visitPost(ForNode* node);
  virtual void visitPost(FuncCall* node);
  virtual void visitPost(MethodNode* node);
  virtual void visitPost(ProgramNode* node);
  virtual void visitPost(VarNode* node);
  virtual void visitPost(AttributeNode* node);
  virtual void visitPost(AssignNode* node);
  virtual void visitPost(NamespaceNode* node);
  virtual void visitPost(ReturnNode* node);
  virtual void visitPost(BlockNode* node);
};
