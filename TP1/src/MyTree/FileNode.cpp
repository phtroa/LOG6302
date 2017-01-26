#include "FileNode.h"

FileNode::FileNode(const std::string& name, std::weak_ptr<ABSNode> parent) : ABSNode(parent), fileName(name) {
}

void FileNode::setFileName(const std::string& name) {
  fileName = name;
}

std::string FileNode::getFileName() const {
  return fileName;
}
