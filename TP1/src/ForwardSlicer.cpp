#include "ForwardSlicer.h"


void ForwardSlicer::slice(const std::string& varName, int lineNumber,
          const CFG& pdGraph, CFG& sliceOUT)
{
  int idOfVar = findBeginOfSlice(varName, lineNumber, pdGraph);
  int currID = 0;
  std::set<int> visited;
  std::map<int,int> oldIDToNewID;
  std::std::vector<int> nodesStack;

  nodesStack.push_back(idOfVar);
  while (!nodesStack.empty()) {
    /* code */
  }
}


int ForwardSlicer::findBeginOfSlice(const std::string& varName, int lineNumber, const CFG& pdGraph)
{
  for (size_t i = 0; i < fgraph.getSize(); i++) {
    std::shared_ptr<CFGNode> node = fgraph.getNode(i);
    if (node->isAssignement() &&
          node->getLValueName() == varName &&
          node->getLineNumber() == lineNumber) {
            return i;
    }

    return -1;
  }

}

virtual const std::vector<int>& ForwardSlicer::getSuccessors(const CFG& pdGraph, int id) const
{
  return pdGraph.getSuccessors(id);
}
