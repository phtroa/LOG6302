#pragma once

#include "ABSNode.h"
#include "InfoType.h"

#include <string>

class AssignNode : public ABSNode {
public:
    AssignNode(const std::string& name, int line);
    ~AssignNode();

    const std::string& getVarName() const;
    void setVarName(const std::string& name);

    void acceptVisitor(ABSASTVisitor* visitor);

private:
  std::string varName;
};
