#include "JumpNode.h"

JumpNode::JumpNode(std::weak_ptr<ABSNode> parent) : ABSNode(parent) {
  incrJump(); //incrémente le nombre de sauts de la méthode
}
