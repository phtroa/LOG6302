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
    visited.insert(idInPdg);
    nodesStack.pop_back();

    const std::vector<int>& sucessors = getSuccessors(pdGraph, idInPdg);
    for (auto it = sucessors.cbegin(); it != sucessors.cend(); it++) {

      if (oldIDToNewID.find(*it) == oldIDToNewID.end()) {
        node = std::shared_ptr<CFGNode>(pdGraph.getNode(*it)->clone());
        node->setId(currID);
        sliceOUT.addNode(node);
        oldIDToNewID[*it] = currID;
        currID++;
      }

      sliceOUT.addVertice(oldIDToNewID[idInPdg], oldIDToNewID[*it]);
      sliceOUT.addReverseVertice(oldIDToNewID[*it], oldIDToNewID[idInPdg]);

      if (visited.find(*it) == visited.end()) {
        nodesStack.push_back(*it);
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
