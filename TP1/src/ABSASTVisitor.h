#pragma once

#include <memory>

class ABSNode;
class AttributeNode;
class ClassNode;
class CondNode;
class BlockNode;
class JumpNode;
class LoopNode;
class MethodNode;
class NamespaceNode;
class ProgramNode;
class ReturnNode;
class VarNode;

//Visitor pattern to visit a tree
//all the *Pre method are called before going into
//the children the *Post are called once all the chldren have been
//encoutered

class ABSASTVisitor {
public:
  virtual ~ABSASTVisitor() = 0;
  virtual void visitPre(ABSNode* node);
  virtual void visitPre(ClassNode* node);
  virtual void visitPre(CondNode* node);
  virtual void visitPre(JumpNode* node);
  virtual void visitPre(LoopNode* node);
  virtual void visitPre(MethodNode* node);
  virtual void visitPre(ProgramNode* node);
  virtual void visitPre(VarNode* node);
  virtual void visitPre(AttributeNode* node);
  virtual void visitPre(NamespaceNode* node);
  virtual void visitPre(ReturnNode* node);
  virtual void visitPre(BlockNode* node);

  virtual void visitBetween(ABSNode* node);
  virtual void visitBetween(ClassNode* node);
  virtual void visitBetween(CondNode* node);
  virtual void visitBetween(JumpNode* node);
  virtual void visitBetween(LoopNode* node);
  virtual void visitBetween(MethodNode* node);
  virtual void visitBetween(ProgramNode* node);
  virtual void visitBetween(VarNode* node);
  virtual void visitBetween(AttributeNode* node);
  virtual void visitBetween(NamespaceNode* node);
  virtual void visitBetween(ReturnNode* node);
  virtual void visitBetween(BlockNode* node);

  virtual void visitPost(ABSNode* node);
  virtual void visitPost(ClassNode* node);
  virtual void visitPost(CondNode* node);
  virtual void visitPost(JumpNode* node);
  virtual void visitPost(LoopNode* node);
  virtual void visitPost(MethodNode* node);
  virtual void visitPost(ProgramNode* node);
  virtual void visitPost(VarNode* node);
  virtual void visitPost(AttributeNode* node);
  virtual void visitPost(NamespaceNode* node);
  virtual void visitPost(ReturnNode* node);
  virtual void visitPost(BlockNode* node);
};
