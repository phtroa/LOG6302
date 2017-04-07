#pragma once

#include "CFGNode.h"

#include <memory>
#include <iostream>
#include <vector>


class CFG
{
  public:
    CFG(const std::string& id);
    CFG(const std::string& id, int ent, int ext);
    void dump(std::ostream& o) const;
    void addNode(std::shared_ptr<CFGNode> node);
    void addVertice(int v1, int v2);
    void addReverseVertice(int v1, int v2);
    int getSize() const;
    std::shared_ptr<CFGNode> getNode(int id) const;
    const std::vector<std::shared_ptr<CFGNode>>& getNodes() const;
    const std::vector<int>& getSuccessors(int id) const;
    const std::vector<int>& getPredecessor(int id) const;

    const std::vector<std::vector<int>>& getVertices() const;
    const std::vector<std::vector<int>>& getReverseVertices() const;

    int getEntry() const;
    int getExit() const;

    void setEntry(int ent);
    void setExit(int ent);
  private:
    int entry;
    int exit;
    std::vector<std::shared_ptr<CFGNode>> nodes;
    std::vector<std::vector<int>> vertices;
    std::vector<std::vector<int>> reverseVertices;
    std::string myID;
};
