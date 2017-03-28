#include "ReachingDef.h"

ReachingDef::ReachingDef()
{
}

ReachingDef::~ReachingDef()
{
}

void ReachingDef::compute(CFG* cfg)
{
  this->cfg = cfg;
  in = new std::set<int>[cfg->getSize()];
  out = new std::set<int>[cfg->getSize()];
  gen = new std::set<int>[cfg->getSize()];
  kill = new std::set<int>[cfg->getSize()];

  fillMap();
  fillGen();
  fillKill();

  iterate();

  varNameToSet.clear();
  delete [] in;
  delete [] out;
  delete [] gen;
  delete [] kill;
}

void ReachingDef::iterate()
{
  bool changed = true;
  std::set<int> diff;
  std::set<int> oldOut;
  while (changed) {
    changed = false;
    std::cout << " in while " << std::endl;
    for (int i = 0; i < cfg->getSize(); i++) {
      if (i == cfg->getEntry()) {
        continue;
      }
      oldOut = out[i];
      //we compute in
      in[i].clear();
      for (auto it = (cfg->getPredecessor(i)).begin();
                it != (cfg->getPredecessor(i)).end(); it++) {
          in[i].insert(out[*it].begin(), out[*it].end());
      }
      //we compute out
      out[i].clear();
      diff.clear();
      std::set_difference(in[i].begin(), in[i].end(),
                            kill[i].begin(), kill[i].end(),
                            inserter(diff, diff.begin()));
      std::set_union(gen[i].begin(), gen[i].end(),
                diff.begin(), diff.end(),
                inserter(out[i], out[i].end()));
      changed = changed || oldOut.size() != out[i].size();
      changed = changed || !std::equal(oldOut.begin(), oldOut.end(), out[i].begin());
    }
  }
}

void ReachingDef::fillMap()
{
  const std::vector<CFGNode*>&  nodes = cfg->getNodes();
  for (int i = 0; i < cfg->getSize(); i++) {
    if (nodes[i]->isAssignement()) {
      varNameToSet[nodes[i]->getLValueName()].insert(nodes[i]->getLineNumber());
    }
  }
}

void ReachingDef::fillGen()
{
  const std::vector<CFGNode*>&  nodes = cfg->getNodes();
  for (int i = 0; i < cfg->getSize(); i++) {
    if (nodes[i]->isAssignement()) {
      gen[i].insert(nodes[i]->getLineNumber());
    }
  }

}

void ReachingDef::fillKill()
{
  const std::vector<CFGNode*>&  nodes = cfg->getNodes();
  for (int i = 0; i < cfg->getSize(); i++) {
    if (nodes[i]->isAssignement()) {
      kill[i] = varNameToSet[nodes[i]->getLValueName()];
    }
  }
}

void ReachingDef::dump(std::ostream& o) const
{
  const std::vector<CFGNode*>&  nodes = cfg->getNodes();
  o  << "\\adjustbox{max width=\\textwidth}{%" << std::endl;
  o  << "\\begin{tabular}{|c|c|c|c|c|c|}" << std::endl;
  o  << "\\hline" << std::endl;
  o  << "label & line num & gen & kill & in & out \\\\" << std::endl;
  o  << "\\hline" << std::endl;
  for (int i = 0; i < cfg->getSize(); i++) {
    o << nodes[i]->getNodeType() << " " << nodes[i]->getLValueName() << " & ";
    o << nodes[i]->getLineNumber() << " & ";
    for (auto it = gen[i].begin(); it != gen[i].end(); it++) {
      o << *it << " ";
    }
    o << " & ";
    for (auto it = kill[i].begin(); it != kill[i].end(); it++) {
      o << *it << " ";
    }
    o << " & ";
    for (auto it = in[i].begin(); it != in[i].end(); it++) {
      o << *it << " ";
    }
    o << " & ";
    for (auto it = out[i].begin(); it != out[i].end(); it++) {
      o << *it << " ";
    }
    o << " \\\\ " << std::endl;
    o  << "\\hline" << std::endl;
  }
  o  << "\\end{tabular}" << std::endl;
  o  << "}" << std::endl;
}

std::ostream& operator<<(std::ostream& o, const ReachingDef& rea) {
  rea.dump(o);
  return o;
}
