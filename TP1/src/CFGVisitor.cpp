#include "CFGVisitor.h"

#include "AssignNode.h"
#include "ClassNode.h"
#include "CondNode.h"
#include "BreakNode.h"
#include "ContinueNode.h"
#include "ForNode.h"
#include "WhileNode.h"
#include "DoWhileNode.h"
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

void CFGVisitor::visitPre(AssignNode* node)
{

  int beginID = localID;
  std::cout << "in visitPre Assign " + std::to_string(beginID) << std::endl;
  std::shared_ptr<CFGNode> assign(
    new CFGAssignNode(beginID,"Assignement" + std::to_string(beginID),
     node->getVarName(), node->getLineNumber())
   );
  assign->setVars(node->getVars());
  localID++;
  graph.back().addNode(assign);

  graph.back().addVertice(currID, beginID);
  graph.back().addReverseVertice(beginID, currID);

  stackBegin.push_back(beginID);
  stackEnd.push_back(beginID);
  currID = beginID;
  std::cout << "Fin visitPre Assign" + std::to_string(beginID) << std::endl;
}

void CFGVisitor::visitPre(VarNode* node)
{
  //In case we have a declaration like int x = 0;
  if (!node->isInitialised()) {
    return;
  }

    int beginID = localID;
    std::cout << "in visitPre varNode Assign " + std::to_string(beginID) << std::endl;
    std::shared_ptr<CFGNode> assign(
       new CFGAssignNode(beginID,
         "VarDecl" + std::to_string(beginID), node->getVarName(), node->getLineNumber()));
    localID++;
    graph.back().addNode(assign);

    graph.back().addVertice(currID, beginID);
    graph.back().addReverseVertice(beginID, currID);

    stackBegin.push_back(beginID);
    stackEnd.push_back(beginID);
    currID = beginID;
    std::cout << "Fin visitPre varNode Assign" + std::to_string(beginID) << std::endl;
}

void CFGVisitor::visitPre(CondNode* node)
{

  int beginID = localID;
  std::cout << "in visitPre cond " + std::to_string(beginID) << std::endl;
  std::shared_ptr<CFGNode> CondEntry(
    new CFGNode(localID++,"CondBegin" + std::to_string(beginID),
     node->getLineNumber())
   );
  graph.back().addNode(CondEntry);

  graph.back().addVertice(currID, beginID);
  graph.back().addReverseVertice(beginID, currID);

  int condID = localID;
  std::shared_ptr<CFGNode> CondNode(
     new CFGNode(localID++,
       "Condition" + std::to_string(beginID), node->getLineNumber())
   );
  CondNode->setVars(node->getVars());
  graph.back().addNode(CondNode);
  graph.back().addVertice(beginID, condID);
  graph.back().addReverseVertice(condID, beginID);
  int endID = localID;
  std::shared_ptr<CFGNode> CondEnd( new CFGNode(localID++,
    "CondEnd" + std::to_string(beginID), node->getLineNumber())
  );
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
}

void CFGVisitor::visitPre(BreakNode* node)
{
  std::cout << "in visitPre Jump" << std::endl;

  int id = localID;
  int breakID = loopStackEnd.back();
  std::shared_ptr<CFGNode> breakNode(
     new CFGNode(localID++,
       "Break", node->getLineNumber())
     );
  graph.back().addNode(breakNode);
  graph.back().addVertice(id, breakID);
  graph.back().addReverseVertice(breakID, id);
  graph.back().addVertice(currID, id);
  graph.back().addReverseVertice(id, currID);

  needlink = false;

  std::cout << "Fin visitPre Jump" << std::endl;
}

void CFGVisitor::visitPre(ContinueNode* node)
{
  std::cout << "in visitPre Jump" << std::endl;

  int id = localID;
  int ContinueID = loopStackEnd.back();
  std::shared_ptr<CFGNode> continueNode(
     new CFGNode(localID++,"Continue", node->getLineNumber())
   );
  graph.back().addNode(continueNode);
  graph.back().addVertice(id, ContinueID);
  graph.back().addReverseVertice(ContinueID, id);

  graph.back().addVertice(currID, id);
  graph.back().addReverseVertice(id, currID);

  needlink = false;

  std::cout << "Fin visitPre Jump" << std::endl;
}

void CFGVisitor::visitPre(WhileNode* node)
{
  std::cout << "in visitPre Loop" << std::endl;

  int beginID = localID;
  std::shared_ptr<CFGNode> loopEntry(
    new CFGNode(localID++,
      "LoopBegin", node->getLineNumber()));
  graph.back().addNode(loopEntry);
  graph.back().addVertice(currID, beginID);
  graph.back().addReverseVertice(beginID, currID);
  int condID = localID;
  std::shared_ptr<CFGNode> CondNode(
    new CFGNode(localID++,"LoopCondition", node->getLineNumber())
);
  CondNode->setVars(node->getVars());
  graph.back().addNode(CondNode);
  int endID = localID;
  std::shared_ptr<CFGNode> loopEnd(
    new CFGNode(localID++,"LoopEnd", node->getLineNumber())
  );
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

  std::cout << "Fin visitPre Loop" << std::endl;
}

void CFGVisitor::visitPre(DoWhileNode* node)
{
  std::cout << "in visitPre Loop" << std::endl;

  int beginID = localID;
  std::shared_ptr<CFGNode> loopEntry(
    new CFGNode(localID++,"LoopBegin", node->getLineNumber())
  );
  graph.back().addNode(loopEntry);
  graph.back().addVertice(currID, beginID);
  graph.back().addReverseVertice(beginID, currID);
  int condID = localID;
  std::shared_ptr<CFGNode> CondNode(
    new CFGNode(localID++,"LoopCondition", node->getLineNumber())
  );
  graph.back().addNode(CondNode);
  int endID = localID;
  std::shared_ptr<CFGNode> loopEnd(
    new CFGNode(localID++,"LoopEnd", node->getLineNumber())
  );
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

  std::cout << "Fin visitPre Loop" << std::endl;
}

void CFGVisitor::visitPre(ForNode* node)
{
  std::cout << "in visitPre Loop" << std::endl;

  int beginID = localID;
  std::shared_ptr<CFGNode> loopEntry(
    new CFGNode(localID++,"LoopBegin", node->getLineNumber())
  );
  graph.back().addNode(loopEntry);
  graph.back().addVertice(currID, beginID);
  graph.back().addReverseVertice(beginID, currID);
  int condID = localID;
  std::shared_ptr<CFGNode> CondNode( new
    CFGNode(localID++,"LoopCondition", node->getLineNumber())
  );
  graph.back().addNode(CondNode);
  int endID = localID;
  std::shared_ptr<CFGNode> loopEnd(
    new CFGNode(localID++,"LoopEnd", node->getLineNumber())
  );
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

  std::shared_ptr<CFGNode> entryNode(
    new CFGNode(entryID,"Entry " + node->getMethodName(), node->getLineNumber())
  );
  graph.back().addNode(entryNode);
  std::shared_ptr<CFGNode> exitNode(
    new CFGNode(exitID,"Exit " + node->getMethodName(), node->getLineNumber())
  );
  graph.back().addNode(exitNode);
  if (node->getNbChildren() < 1) {
    graph.back().addVertice(currID, exitID);
    graph.back().addReverseVertice(exitID, currID);
  }

  stackBegin.push_back(entryID);
  stackEnd.push_back(exitID);

  std::cout << "Fin visitPre Method" << std::endl;
}

void CFGVisitor::visitPre(ReturnNode* node)
{
  std::cout << "in visitPre return" << std::endl;
  int beginID = localID;
  localID++;
  std::shared_ptr<CFGNode> returnEntry(
    new CFGNode(beginID,"Return", node->getLineNumber())
  );
  returnEntry->setVars(node->getVars());
  graph.back().addNode(returnEntry);

  graph.back().addVertice(currID, beginID);
  graph.back().addReverseVertice(beginID, currID);
  graph.back().addVertice(beginID, exitID);
  graph.back().addReverseVertice(exitID, beginID);

  needlink = false;

  std::cout << "Fin visitPre return" << std::endl;
}

void CFGVisitor::visitPost(AssignNode* node)
{
  std::cout << "in visitPost Assign" << std::endl;
  stackBegin.pop_back();
  stackEnd.pop_back();
  std::cout << "Fin visitPost Assign" << std::endl;
}

void CFGVisitor::visitPost(VarNode* node)
{
  if (!node->isInitialised()) {
    return;
  }
  std::cout << "in visitPost VarDecl" << std::endl;
  stackBegin.pop_back();
  stackEnd.pop_back();
  std::cout << "Fin visitPost VarDecl" << std::endl;
}

void CFGVisitor::visitPost(MethodNode* node)
{
  std::cout << "in visitPost Method" << std::endl;
  int endID = stackEnd.back();
  if (needlink) {
    graph.back().addVertice(currID, endID);
    graph.back().addReverseVertice(endID, currID);
  }
  needlink = true;
  stackBegin.pop_back();
  stackEnd.pop_back();
  //TODO clean up
  std::shared_ptr<CFGNode> entryNode(new CFGNode(localID,"Entry System", 0));
  graph.back().addNode(entryNode);
  //link entry system to the Method entry
  graph.back().addVertice(localID, graph.back().getEntry());
  graph.back().addReverseVertice(graph.back().getEntry(), localID);
  //link entry system to the Method exit
  graph.back().addVertice(localID, graph.back().getExit());
  graph.back().addReverseVertice(graph.back().getExit(), localID);


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

void CFGVisitor::visitPost(WhileNode* node)
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
}

void CFGVisitor::visitPost(DoWhileNode* node)
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
}

void CFGVisitor::visitPost(ForNode* node)
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
}

void CFGVisitor::visitPost(ProgramNode* node)
{
}

 void CFGVisitor::visitPost(BlockNode* node)
{
}

 void CFGVisitor::visitPost(ReturnNode* node)
{
}


std::vector<CFG>& CFGVisitor::getGraph()
{
  return graph;
}

void CFGVisitor::dump(std::ostream& o) const
{
    std::cout << " digraph G {" << std::endl;
    for (auto it = graph.begin(); it !=  graph.end(); it++) {
      it->dump(o);
    }
    std::cout << "}" << std::endl;
}
