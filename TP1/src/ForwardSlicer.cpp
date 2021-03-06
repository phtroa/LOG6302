#include "ForwardSlicer.h"


void ForwardSlicer::slice(const std::string& varName, int lineNumber,
          const CFG& pdGraph, CFG& sliceOUT)
{
  int idOfVar = findBeginOfSlice(varName, lineNumber, pdGraph);
  if (idOfVar == -1) {
    std::cerr << "find not fonctional" << std::endl;
    return;
  }
  int currID = 0;
  int idInPdg = -1;
  std::set<int> visited;
  std::set<int> isScheduled;
  std::map<int,int> oldIDToNewID;
  std::vector<int> nodesStack;

  idInPdg = idOfVar;
  std::shared_ptr<CFGNode> node(pdGraph.getNode(idOfVar)->clone());
  node->setId(currID);
  sliceOUT.addNode(node);
  oldIDToNewID[idInPdg] = currID;
  currID++;

  nodesStack.push_back(idOfVar);
  while (!nodesStack.empty()) {
    idInPdg = nodesStack.back();
    nodesStack.pop_back();
    if (visited.find(idInPdg) != visited.end()) {
      continue;
    }
    visited.insert(idInPdg);

    const std::vector<int>& sucessors = getSuccessors(pdGraph, idInPdg);
    for (auto it = sucessors.cbegin(); it != sucessors.cend(); it++) {

      //we create a node only if it doesn't already exist
      if (oldIDToNewID.find(*it) == oldIDToNewID.end()) {
        node = std::shared_ptr<CFGNode>(pdGraph.getNode(*it)->clone());
        node->setId(currID);
        sliceOUT.addNode(node);
        oldIDToNewID[*it] = currID;
        currID++;
      }

      sliceOUT.addVertice(oldIDToNewID[idInPdg], oldIDToNewID[*it]);
      sliceOUT.addReverseVertice(oldIDToNewID[*it], oldIDToNewID[idInPdg]);

      if (visited.find(*it) == visited.end() && isScheduled.find(*it) == isScheduled.end()) {
        nodesStack.push_back(*it);
        isScheduled.insert(idInPdg);
      }
    }
  }
}


int ForwardSlicer::findBeginOfSlice(const std::string& varName, int lineNumber, const CFG& pdGraph)
{
  for (size_t i = 0; i < pdGraph.getSize(); i++) {
    std::shared_ptr<CFGNode> node = pdGraph.getNode(i);
    if (node->isAssignement() &&
          node->getLValueName() == varName &&
          node->getLineNumber() == lineNumber) {
            return i;
    }
  }

  return -1;
}

const std::vector<int>& ForwardSlicer::getSuccessors(const CFG& pdGraph, int id) const
{
  return pdGraph.getSuccessors(id);
}
