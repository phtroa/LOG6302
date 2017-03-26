#include "Dominator.h"

Dominator::Dominator() : domTreeParent(nullptr)
{
}

std::shared_ptr<DomTree> Dominator::compute(CFG* cfg)
{
  this->cfg = cfg;
  domTreeParent = new int[cfg->getSize()];
  for (int i = 0; i < cfg->getSize(); i++)
    domTreeParent[i] = -1;

  makeDomTree();
  std::shared_ptr<DomTree> domTree = convertToCFG();

  delete [] domTreeParent;
  domTreeParent = nullptr;
  treeNodes.clear();

  return domTree;
}


std::shared_ptr<DomTree> Dominator::convertToCFG()
{
  std::shared_ptr<DomTree> domTree(new DomTree(cfg->getNodes(), domTreeParent, cfg->getSize()));
  return domTree;
}

void Dominator::makeDFSTree()
{
  std::vector<int> stack;
  std::set<int> visited;
  stack.push_back(getEntry());
  while (!stack.empty()) {
    int top = stack.back();
    stack.pop_back();
    if (visited.find(top) != visited.end()) {
      continue;
    }

    std::cout << "Avant successeur " << top << " size " << cfg->getSize() << std::endl;
    for (auto it = (getSuccessors(top)).cbegin(); it != (getSuccessors(top)).cend(); it++) {
      std::cout << "Apres successeur " << top << ":" << *it << std::endl;
      if (visited.find(*it) == visited.end() && *it != top) {
        stack.push_back(*it);
        domTreeParent[*it] = top;
      }
    }
    visited.insert(top);
    treeNodes.insert(top);
  }
}

void Dominator::makeDomTree()
{
  makeDFSTree();
  bool changed = true;
  while (changed) {
    changed = false;
    int currNode = 0;
    while (currNode < cfg->getSize()) {
      int c = currNode++;
      if ((getPredecessor(c)).size() == 0) {
        continue;
      }

      int currParent = 0;
      int parent = (getPredecessor(c))[currParent++];
      while (currParent < (getPredecessor(c)).size()) {
        int p = (getPredecessor(c))[currParent++];
        if (treeNodes.find(p) == treeNodes.end()) {
          continue;
        }
        parent = nca(parent, p);
      }
      if (domTreeParent[c] != parent) {
        domTreeParent[c] = parent;
        changed = true;
      }
    }
  }
}

int Dominator::nca(int node1, int node2)
{
  std::set<int> path;
  int c = node1;
  while (c != -1) {
    path.insert(c);
    c = domTreeParent[c];
  }

  c = node2;
  while (c != -1 && path.find(c) == path.end()) {
    c = domTreeParent[c];
  }

  return c;
}

const std::vector<int>& Dominator::getSuccessors(int id)
{
  return cfg->getSuccessors(id);
}

const std::vector<int>& Dominator::getPredecessor(int id)
{
  return cfg->getPredecessor(id);
}

int Dominator::getEntry() const
{
  return cfg->getEntry();
}

int Dominator::getExit() const
{
  return cfg->getExit();
}
