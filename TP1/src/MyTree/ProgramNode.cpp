#include "ProgramNode.h"

ProgramNode::ProgramNode() : ABSNode(nullptr) {
}

//Ces méthodes ne devraient jamais être appelées
void ProgramNode::incrCond() {
}

void ProgramNode::incrLoop() {
}

void ProgramNode::incrJump()  {
}

void ProgramNode::incrVar() {
}
