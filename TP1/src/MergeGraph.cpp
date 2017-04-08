#include "MergeGraph.h"

//merge vertices, both graph should have the same nodes
void MergeGraph::merge(const CFG& fgraph, const CFG& sgraph, CFG& res)
{

  for (size_t i = 0; i < fgraph.getSize(); i++) {
    std::shared_ptr<CFGNode> node = fgraph.getNode(i);
    res.addNode(node);
  }

  std::set<int>* idToNei = new std::set<int>[fgraph.getSize()];
  //for the first graph
  const std::vector<std::vector<int>>& verticesf = fgraph.getVertices();
  for (int i = 0; i < verticesf.size(); i++) {
    for (auto nei = (verticesf[i]).cbegin(); nei != (verticesf[i]).cend(); nei++) {
      idToNei[i].insert(*nei);
    }
  }

  //for the second graph
  const std::vector<std::vector<int>>& verticesS = sgraph.getVertices();
  for (int i = 0; i < verticesS.size(); i++) {
    for (auto nei = (verticesS[i]).cbegin(); nei != (verticesS[i]).cend(); nei++) {
      idToNei[i].insert(*nei);
    }
  }

  //we put every vertices in the merged graphe
  for (size_t i = 0; i < fgraph.getSize(); i++) {
    for (auto it = idToNei[i].begin(); it != idToNei[i].end(); it++) {
      res.addVertice(i, *it);
      res.addReverseVertice(*it, i);
    }
  }

  delete [] idToNei;
}
