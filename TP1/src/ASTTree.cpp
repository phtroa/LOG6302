#include "ASTTree.h"

void ASTTree::setRoot(std::shared_ptr<ABSNode> root) {
  this->root = root;
}

std::shared_ptr<ABSNode> ASTTree::getRoot() {
  return root;
}

void ASTTree::linkParentToChild(std::shared_ptr<ABSNode> parent, std::shared_ptr<ABSNode> child) {
  child->setParent(parent);
  parent->addChild(child);
}

void ASTTree::acceptVisitor(ABSASTVisitor* visitor) {
  if (root != nullptr) {
    root->acceptVisitor(visitor);
  }
}
