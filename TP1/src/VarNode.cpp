#include "VarNode.h"

VarNode::VarNode(std::weak_ptr<ABSNode> parent) : ABSNode(parent) {
  incrVar(); //incrémente le nombre de boucles de la méthode
}
