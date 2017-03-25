#include "CFG.h"

CFG::CFG(const std::string& id, int ent, int ext) : myID(id), entry(ent), exit(ext)
{
}

void CFG::dump(std::ostream& o) const
{
  std::string idInGraph;
  for (auto it = nodes.begin(); it != nodes.end(); it++) {
    o << myID << *it << std::endl;
  }

  std::string idsrc;
  std::string iddest;
  for (int i = 0; i < vertices.size(); i++) {
    idsrc = myID + std::to_string(i);
    for (int j = 0; j < vertices[i].size(); j++) {
      iddest = myID + std::to_string(vertices[i][j]);
      o << idsrc << " -> " << iddest << std::endl;
    }
  }
}

void CFG::addNode(const CFGNode& node)
{
  nodes.push_back(node);
  vertices.push_back(std::vector<int>());
  reverseVertices.push_back(std::vector<int>());
}

void CFG::addVertice(int v1, int v2)
{
  vertices[v1].push_back(v2);
}

void CFG::addReverseVertice(int v1, int v2)
{
  reverseVertices[v1].push_back(v2);
}

CFGNode& CFG::getNode(int id)
{
    return nodes[id];
}


const std::vector<int>& CFG::getSuccessors(int id) const
{
  return vertices[id];
}

const std::vector<int>& CFG::getPredecessor(int id) const
{
  return reverseVertices[id];
}

int CFG::getEntry() const
{
  return entry;
}

int CFG::getExit() const
{
  return exit;
}

void CFG::setEntry(int ent)
{
  entry = ent;
}

void CFG::setExit(int ent)
{
  exit = ent;
}

int CFG::getSize() const
{
  return nodes.size();
}

const std::vector<CFGNode>& CFG::getNodes() const
{
  return nodes;
}
