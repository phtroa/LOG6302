#include "CFGVisitor.h"

#include "ClassNode.h"
#include "CondNode.h"
#include "JumpNode.h"
#include "LoopNode.h"
#include "MethodNode.h"
#include "NamespaceNode.h"
#include "ProgramNode.h"
#include "ReturnNode.h"
#include "VarNode.h"
#include "AttributeNode.h"

#include <typeinfo>

CFGVisitor::CFGVisitor() : localID(0), globalID(0), needlink(true)
{}

CFGVisitor::~CFGVisitor()
{}

void CFGVisitor::visitPre(CondNode* node)
{

  int beginID = localID;
  std::cout << "in visitPre cond " + std::to_string(beginID) << std::endl;
  CFGNode CondEntry(localID++,"CondBegin" + std::to_string(beginID), node->getLineNumber());
  graph.back().addNode(CondEntry);

  graph.back().addVertice(currID, beginID);
  graph.back().addReverseVertice(beginID, currID);

  int condID = localID;
  CFGNode CondNode(localID++,"Condition" + std::to_string(beginID), node->getLineNumber());
  graph.back().addNode(CondNode);
  graph.back().addVertice(beginID, condID);
  graph.back().addReverseVertice(condID, beginID);
  int endID = localID;
  CFGNode CondEnd(localID++,"CondEnd" + std::to_string(beginID), node->getLineNumber());
  graph.back().addNode(CondEnd);
  if (node->getNbChildren() < 2) {
    graph.back().addVertice(condID, endID);
    graph.back().addReverseVertice(endID, condID);
  }
  ifStackBegin.push_back(condID);
  ifStackEnd.push_back(endID);
  stackBegin.push_back(condID);
  stackEnd.push_back(endID);
  currID = condID;
  //creation des noeuds
  // std::shared_ptr<CFGTreeNode> cond(new CFGCondNode(beginID, endID, condID));
  // currNode->addChild(cond);
  // cond->setParent(currNode);
  // currNode = cond;
  std::cout << "Fin visitPre cond" + std::to_string(beginID) << std::endl;
}

void CFGVisitor::visitBetween(CondNode* node)
{
  int endif = stackEnd.back();
  int beginif = stackBegin.back();
  std::cout << "in visitBetween cond " + std::to_string(beginif) << std::endl;
  if (needlink) {
    graph.back().addVertice(currID, endif);
    graph.back().addReverseVertice(endif, currID);
  }
  needlink = true;
  currID = beginif;
  std::cout << "Fin visitBetween cond" + std::to_string(beginif) << std::endl;
}

 void CFGVisitor::visitPre(BlockNode* node)
{
  //creation des noeuds
  // std::shared_ptr<CFGTreeNode> block(new CFGBlockNode());
  // block->setParent(currNode);
  // currNode->addChild(block);
  // currNode = block;
}

void CFGVisitor::visitPre(JumpNode* node)
{
  std::cout << "in visitPre Jump" << std::endl;

  int id = localID;
  int breakID = loopStackEnd.back();
  int ContinueID = loopStackEnd.back();
  if (true) { //TODO change this
    CFGNode breakNode(localID++,"Break", node->getLineNumber());
    graph.back().addNode(breakNode);
    graph.back().addVertice(id, breakID);
    graph.back().addReverseVertice(breakID, id);
  }
  else {
    CFGNode continueNode(localID++,"Continue", node->getLineNumber());
    graph.back().addNode(continueNode);
    graph.back().addVertice(id, ContinueID);
    graph.back().addReverseVertice(ContinueID, id);
  }

  graph.back().addVertice(currID, id);
  graph.back().addReverseVertice(id, currID);

  needlink = false;
  // std::shared_ptr<CFGTreeNode> jump(new CFGBreakNode(id, breakID));
  // currNode->addChild(jump);
  // jump->setParent(currNode);
  // currNode = jump;

  std::cout << "Fin visitPre Jump" << std::endl;
}

void CFGVisitor::visitPre(LoopNode* node)
{
  std::cout << "in visitPre Loop" << std::endl;

  int beginID = localID;
  CFGNode loopEntry(localID++,"LoopBegin", node->getLineNumber());
  graph.back().addNode(loopEntry);
  graph.back().addVertice(currID, beginID);
  graph.back().addReverseVertice(beginID, currID);
  int condID = localID;
  CFGNode CondNode(localID++,"LoopCondition", node->getLineNumber());
  graph.back().addNode(CondNode);
  int endID = localID;
  CFGNode loopEnd(localID++,"LoopEnd", node->getLineNumber());
  graph.back().addNode(loopEnd);
  loopStackBegin.push_back(beginID);
  loopStackEnd.push_back(endID);

  graph.back().addVertice(beginID, condID);
  graph.back().addReverseVertice(condID, beginID);
  graph.back().addVertice(condID, endID);
  graph.back().addReverseVertice(endID, condID);
  currID = condID;

  stackBegin.push_back(condID);
  stackEnd.push_back(endID);

  // std::shared_ptr<CFGTreeNode> loop(new CFGLoopNode(beginID, endID, condID));
  // currNode->addChild(loop);
  // loop->setParent(currNode);
  // currNode = loop;
  std::cout << "Fin visitPre Loop" << std::endl;
}

void CFGVisitor::visitPre(MethodNode* node)
{
  std::cout << "in visitPre Method" << std::endl;

  localID = 0;
  currID = 0;
  entryID = localID;
  localID++;
  exitID = localID;
  localID++;
  graph.push_back(CFG(node->getMethodName() + std::to_string(globalID), entryID, exitID));
  globalID++;

  CFGNode entryNode(entryID,"Entry " + node->getMethodName(), node->getLineNumber());
  graph.back().addNode(entryNode);
  CFGNode exitNode(exitID,"Exit " + node->getMethodName(), node->getLineNumber());
  graph.back().addNode(exitNode);
  if (node->getNbChildren() < 1) {
    graph.back().addVertice(currID, exitID);
    graph.back().addReverseVertice(exitID, currID);
  }

  stackBegin.push_back(entryID);
  stackEnd.push_back(exitID);

  // std::shared_ptr<CFGTreeNode> method(new CFGMethodNode(entryID, exitID));
  // tree = method;
  // currNode = tree;

  std::cout << "Fin visitPre Method" << std::endl;
}

void CFGVisitor::visitPre(ReturnNode* node)
{
  std::cout << "in visitPre return" << std::endl;
  int beginID = localID;
  localID++;
  CFGNode returnEntry(beginID,"Return", node->getLineNumber());
  graph.back().addNode(returnEntry);

  graph.back().addVertice(currID, beginID);
  graph.back().addReverseVertice(beginID, currID);
  graph.back().addVertice(beginID, exitID);
  graph.back().addReverseVertice(exitID, beginID);

  needlink = false;
  // std::shared_ptr<CFGTreeNode> retNode(new CFGReturnNode(beginID, exitID));
  // currNode->addChild(retNode);
  // retNode->setParent(currNode);
  // currNode = retNode;

  std::cout << "Fin visitPre return" << std::endl;
}

void CFGVisitor::visitPost(MethodNode* node)
{
  std::cout << "in visitPost Method" << std::endl;
  //CFG* currGraph = &(graph.back());
  //CFGTreeVisitor visitor(currGraph);
  //tree->acceptVisitor(&visitor);
  int endID = stackEnd.back();
  if (needlink) {
    graph.back().addVertice(currID, endID);
    graph.back().addReverseVertice(endID, currID);
  }
  needlink = true;
  stackBegin.pop_back();
  stackEnd.pop_back();

  localID = 0;
  entryID = 0;
  exitID = 0;
  std::cout << "Fin visitPost Method" << std::endl;
}

void CFGVisitor::visitPost(CondNode* node)
{
  std::cout << "in visitPost cond" << std::endl;
  //currNode = currNode->getParent();
  ifStackBegin.pop_back();
  ifStackEnd.pop_back();
  int beginID = stackBegin.back();
  int endID = stackEnd.back();
  if (needlink) {
    graph.back().addVertice(currID, endID);
    graph.back().addReverseVertice(endID, currID);
  }
  needlink = true;
  currID = endID;
  stackBegin.pop_back();
  stackEnd.pop_back();
  std::cout << "in visitPost cond" << std::endl;
}

void CFGVisitor::visitPost(JumpNode* node)
{
  //currNode = currNode->getParent();
}

void CFGVisitor::visitPost(LoopNode* node)
{
  loopStackBegin.pop_back();
  loopStackEnd.pop_back();
  int endid = stackEnd.back();
  int beginID = stackBegin.back();
  stackBegin.pop_back();
  stackEnd.pop_back();
  if (needlink) {
    graph.back().addVertice(currID, beginID);
    graph.back().addReverseVertice(beginID, currID);
  }
  needlink = true;
  currID = endid;
  //currNode = currNode->getParent();
}

void CFGVisitor::visitPost(ProgramNode* node)
{
    std::cout << " digraph G {" << std::endl;
    for (auto it = graph.begin(); it !=  graph.end(); it++) {
      it->dump(std::cout);
    }
    std::cout << "}" << std::endl;
}

 void CFGVisitor::visitPost(BlockNode* node)
{
  //currNode = currNode->getParent();
}

 void CFGVisitor::visitPost(ReturnNode* node)
{
  //currNode = currNode->getParent();
}


std::vector<CFG>& CFGVisitor::getGraph()
{
  return graph;
}
