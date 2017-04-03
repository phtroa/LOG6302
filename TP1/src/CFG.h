#pragma once

#include "CFGNode.h"

#include <iostream>
#include <vector>


class CFG
{
  public:
    CFG(const std::string& id);
    CFG(const std::string& id, int ent, int ext);
    ~CFG();
    void dump(std::ostream& o) const;
    void addNode(CFGNode* node);
    void addVertice(int v1, int v2);
    void addReverseVertice(int v1, int v2);
    int getSize() const;
    CFGNode* getNode(int id);
    const std::vector<CFGNode*>& getNodes() const;
    const std::vector<int>& getSuccessors(int id) const;
    const std::vector<int>& getPredecessor(int id) const;

    int getEntry() const;
    int getExit() const;

    void setEntry(int ent);
    void setExit(int ent);
  private:
    int entry;
    int exit;
    std::vector<CFGNode*> nodes;
    std::vector<std::vector<int>> vertices;
    std::vector<std::vector<int>> reverseVertices;
    std::string myID;
};
