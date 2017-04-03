#include "CDGraphBuilder.h"

void CDGraphBuilder::build(std::shared_ptr<DomTree> pTree, const CFG& graphIN, CFG& graphOUT)
{
  for (size_t i = 0; i < pTree->getSize(); i++) {
    CFGNode* node = pTree->getNode(i);
    graphOUT.addNode(node->clone());
  }
  //we must compute S
  std::vector<std::pair<int,int>> S;
  builS(S, pTree, graphIN);

  //begining of the algorithm
  std::set<std::pair<int,int>> Ecd;
  for (auto it = S.begin(); it != S.end(); it++) {
    int node = it->second;
    do {
      Ecd.insert(std::make_pair(it->first,node));
      node = pTree->getiDom(node);
    } while(node != pTree->getiDom(it->first) && node != -1);
  }
  //we add the lattices
  for (auto it = Ecd.begin(); it != Ecd.end(); it++) {
    graphOUT.addVertice(it->first,it->second);
  }
}

void CDGraphBuilder::builS(std::vector<std::pair<int,int>>& S,
                                std::shared_ptr<DomTree> pTree,
                                const CFG& graphIN)
{
  for (int x = 0; x < graphIN.getSize(); x++) {
    for (int j = 0; j < graphIN.getSuccessors(x).size(); j++) {
      int y = graphIN.getSuccessors(x)[j];
      if (x == y) {
        continue;
      }
      if (pTree->inS(x,y)) {
        S.push_back(std::pair<int,int>(x,y));
      }
    }
  }
}

void CDGraphBuilder::dumpS(std::ostream& o, const std::vector<std::pair<int,int>>& S) const
{
  for (size_t i = 0; i < S.size(); i++) {
    o << S[i].first << "," << S[i].second << std::endl;
   }
}
