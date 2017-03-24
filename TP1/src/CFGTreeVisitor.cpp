#include "CFGTreeVisitor.h"
#include "CFGBlockNode.h"
#include "CFGBreakNode.h"
#include "CFGCondNode.h"
#include "CFGLoopNode.h"
#include "CFGReturnNode.h"
#include "CFGMethodNode.h"

#include <iostream>

CFGTreeVisitor::CFGTreeVisitor(CFG* cfg) : currCFG(cfg)
{}

void CFGTreeVisitor::visit(const CFGBlockNode* node)
{
  std::cout << "in BlockNode " << std::endl;
  int currID = node->getBeginID();
  std::shared_ptr<CFGTreeNode> child;
  std::shared_ptr<CFGTreeNode> nchild;
  if (node->getNbChildren() == 0 ) {
    currCFG->addVertice(entryID, exitID);
    return;
  }

  child = node->getNode(0);
  currCFG->addVertice(entryID, child->getBeginID());
  for (int i = 0; i < node->getNbChildren() - 1; i++) {
    child = node->getNode(i);
    nchild = node->getNode(i+1);
    if (child->isLinkNeeded()) {
      currCFG->addVertice(child->getEndID(), nchild->getBeginID());
    }
  }
  if (child->isLinkNeeded()) {
    currCFG->addVertice(nchild->getEndID(), exitID);
  }
  std::cout << "Fin BlockNode " << std::endl;
}

void CFGTreeVisitor::visit(const CFGLoopNode* node)
{
  std::cout << "in CFGLoopNode " << std::endl;
  int beginID = node->getBeginID();
  int condID = node->getCondID();
  int endID = node->getEndID();
  std::shared_ptr<CFGTreeNode> child;
  currCFG->addVertice(beginID, condID);
  currCFG->addVertice(condID, endID);

  for (int i = 0; i < node->getNbChildren(); i++) {
    child = node->getNode(i);
    currCFG->addVertice(condID, child->getBeginID());
  }
  if (child->isLinkNeeded()) {
    currCFG->addVertice(child->getEndID(), condID);
  }
  std::cout << "Fin CFGLoopNode " << std::endl;
}

void CFGTreeVisitor::visit(const CFGBreakNode* node)
{
  std::cout << "in CFGBreakNode " << std::endl;
  currCFG->addVertice(node->getBeginID(), node->getEndID());
  std::cout << "Fin CFGBreakNode " << std::endl;
}

void CFGTreeVisitor::visit(const CFGCondNode* node)
{
  std::cout << "in CFGCondNode " << std::endl;
  int beginID = node->getBeginID();
  int condID = node->getCondID();
  int endID = node->getEndID();
  std::shared_ptr<CFGTreeNode> child;
  currCFG->addVertice(beginID, condID);

  for (int i = 0; i < node->getNbChildren(); i++) {
    child = node->getNode(i);
    currCFG->addVertice(condID, child->getBeginID());
    if (child->isLinkNeeded()) {
      currCFG->addVertice(child->getEndID(), endID);
    }
  }
  if (node->getNbChildren() < 2)  {
    currCFG->addVertice(condID, endID);
  }
  std::cout << "Fin CFGCondNode " << std::endl;
}

void CFGTreeVisitor::visit(const CFGReturnNode* node)
{
  std::cout << "in CFGReturnNode " << std::endl;
  currCFG->addVertice(node->getEndID(), exitID);
  std::cout << "Fin CFGReturnNode " << std::endl;
}

void CFGTreeVisitor::visit(const CFGMethodNode* node)
{
  std::cout << "in CFGMethodNode " << std::endl;
  entryID = node->getBeginID();
  exitID = node->getEndID();
  int currID = node->getBeginID();
  std::shared_ptr<CFGTreeNode> child;
  std::shared_ptr<CFGTreeNode> nchild;
  if (node->getNbChildren() == 0 ) {
    currCFG->addVertice(entryID, exitID);
    return;
  }

  std::cout << "in CFGMethodNode 2" << std::endl;
  child = node->getNode(0);
  nchild = child;
  currCFG->addVertice(entryID, child->getBeginID());
  for (int i = 0; i < node->getNbChildren() - 1; i++) {
    child = node->getNode(i);
    nchild = node->getNode(i+1);
    if (child->isLinkNeeded()) {
      currCFG->addVertice(child->getEndID(), nchild->getBeginID());
    }
  }
  if (nchild->isLinkNeeded()) {
    currCFG->addVertice(nchild->getEndID(), exitID);
  }
  std::cout << "Fin CFGMethodNode " << std::endl;
}
