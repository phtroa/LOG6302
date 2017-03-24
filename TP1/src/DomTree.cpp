#include "DomTree.h"

DomTree::DomTree(const std::vector<CFGNode>& nodes, int* links, int size) : mNodes(nodes)
{
  for (size_t i = 0; i < size; i++) {
    mLinks.push_back(links[i]);
  }
}

void DomTree::dump(std::ostream& o) const
{

  std::cout << " digraph G {" << std::endl;
  for (auto it = mNodes.begin(); it != mNodes.end(); it++) {
    it->dump(o);
  }

  std::string idsrc;
  std::string idest;
  for (int i = 0; i < mLinks.size(); i++) {
    if (mLinks[i] == -1) {
      continue;
    }
    idsrc = std::to_string(mLinks[i]);
    idest = std::to_string(i);
    o << idsrc << " -> " << idest << std::endl;
  }
  std::cout << "}" << std::endl;
}

std::ostream& operator<<(std::ostream& o, const DomTree& tree) {
  tree.dump(o);

  return o;
}
