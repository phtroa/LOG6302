#pragma once

#include "ABSNode.h"

#include <string>

class VarNode : public ABSNode {
public:
    VarNode(const std::string& name, int line, bool init = false);
    ~VarNode();

    std::string getVarName() const;
    void setVarName(const std::string& name);
    bool isInitialised() const;
    void setInit(bool init);

    void acceptVisitor(ABSASTVisitor* visitor);
private:
  std::string varName;
  bool isInit;
};
