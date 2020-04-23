#pragma once
#include "Node.h"
#include "Player.h"

class AttackTargetTask : public Node {
private:
	Player* playerAI;

public:
	AttackTargetTask(Player* _playerAI) : playerAI(_playerAI) {}

};