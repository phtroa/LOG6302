#include "LoopNode.h"

LoopNode::LoopNode(std::weak_ptr<ABSNode> parent) : ABSNode(parent) {
  incrLoop(); //incrémente le nombre de boucles de la méthode
}
