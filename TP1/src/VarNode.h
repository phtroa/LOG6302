#pragma once

#include "ABSNode.h"

#include <string>

class VarNode : public ABSNode {
public:
    VarNode(const std::string& name);

    std::string getVarName() const;
    void setVarName(const std::string& name);

    void acceptVisitor(ABSASTVisitor* visitor);
private:
  std::string varName;
};
