#pragma once

#include "ABSNode.h"
#include "InfoType.h"

#include <string>

class AttributeNode : public ABSNode {
public:
    AttributeNode(const std::string& name,
                  const InfoType& type,
                  int visibility = 0);
    ~AttributeNode();

    std::string getAttName() const;
    void setAttName(const std::string& name);

    int getVisibility() const;

    const InfoType& getType() const;

    void acceptVisitor(ABSASTVisitor* visitor);
    
private:
  std::string attName;
  InfoType ifType;
  int attVsblt;
};
