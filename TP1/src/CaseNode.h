#pragma once

#include "BlockNode.h"

class CaseNode : public BlockNode
{
public:
  CaseNode(int line);
  ~CaseNode();

  void acceptVisitor(ABSASTVisitor* visitor);

};
