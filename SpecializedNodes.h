#pragma once
#include "Node.h"
#include "Player.h"

class AttackTargetTask : public Node {
private:
	Player* playerAI;

public:
	AttackTargetTask(Player* _playerAI) : playerAI(_playerAI) {}
	virtual bool run() override {
		return playerAI->attackAMeleeTarget();
	}
};

class FindTargetTask : public Node {
private:
	Player* playerAI;

public:
	FindTargetTask(Player* _playerAI) : playerAI(_playerAI) {}
	virtual bool run() override {
		return playerAI->findClosestTarget();
	}
};

class TurnTowardTargetTask : public Node {
private:
	Player* playerAI;

public:
	TurnTowardTargetTask(Player* _playerAI) : playerAI(_playerAI) {}
	virtual bool run() override {
		playerAI->turnTowardClosestTarget();
		return true;
	}
};

class AdvanceWhileNotBlockedTask : public Node {
private:
	Player* playerAI;

public:
	AdvanceWhileNotBlockedTask(Player* _playerAI) : playerAI(_playerAI) {}
	virtual bool run() override {
		//TODO
	}
};

class BlockedByTargetTask : public Node {
private:
	Player* playerAI;

public:
	BlockedByTargetTask(Player* _playerAI) : playerAI(_playerAI) {}
	virtual bool run() override {
		//TODO
	}
};

class ChooseDirectionInFrontOfWallTask : public Node {
private:
	Player* playerAI;

public:
	ChooseDirectionInFrontOfWallTask(Player* _playerAI) : playerAI(_playerAI) {}
	virtual bool run() override {
		//TODO
	}
};

class AdvanceOnlyOneSquareTask : public Node {
private:
	Player* playerAI;

public:
	AdvanceOnlyOneSquareTask(Player* _playerAI) : playerAI(_playerAI) {}
	virtual bool run() override {
		//TODO
	}
};