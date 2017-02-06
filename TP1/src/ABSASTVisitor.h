#pragma once

#include <memory>

class ABSNode;
class ClassNode;
class CondNode;
class JumpNode;
class LoopNode;
class MethodNode;
class ProgramNode;
class VarNode;

//Visitor pattern to visit a tree
//all the *Pre method are called before going into
//the children the *Post are called once all the chldren have been
//encoutered

class ABSASTVisitor {
public:
  virtual void visitPre(ClassNode* node) = 0;
  virtual void visitPre(CondNode* node) = 0;
  virtual void visitPre(JumpNode* node) = 0;
  virtual void visitPre(LoopNode* node) = 0;
  virtual void visitPre(MethodNode* node) = 0;
  virtual void visitPre(ProgramNode* node) = 0;
  virtual void visitPre(VarNode* node) = 0;

  virtual void visitPost(ClassNode* node) = 0;
  virtual void visitPost(CondNode* node) = 0;
  virtual void visitPost(JumpNode* node) = 0;
  virtual void visitPost(LoopNode* node) = 0;
  virtual void visitPost(MethodNode* node) = 0;
  virtual void visitPost(ProgramNode* node) = 0;
  virtual void visitPost(VarNode* node) = 0;
};
