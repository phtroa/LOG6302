#pragma once

#include <string>

#include "ABSNode.h"

class FileNode : public ABSNode {
public:
  FileNode(const std::string& name, std::weak_ptr<ABSNode> parent);
  void setFileName(const std::string& name);
  std::string getFileName() const;

private:
  std::string fileName;
};
