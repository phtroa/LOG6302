#include "JumpNode.h"

CondNode::CondNode(std::weak_ptr<ABSNode> parent) : ABSNode(parent) {
  incrCond(); //incrémente le nombre de conditions de la méthode
}
