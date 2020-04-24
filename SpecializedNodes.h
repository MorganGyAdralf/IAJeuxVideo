#pragma once
#include "Node.h"
#include "Player.h"

class AttackTargetTask : public Node {
private:
	Player* playerAI;

public:
	AttackTargetTask(Player* _playerAI) : playerAI(_playerAI) {
		nodeName = "Task : attack target";
		nodeType = NodeType::SpecializedNode;
	}
	virtual bool run() override {
		_getch();
		return playerAI->attackAMeleeTarget();
	}
};

class FindTargetTask : public Node {
private:
	Player* playerAI;

public:
	FindTargetTask(Player* _playerAI) : playerAI(_playerAI) {
		nodeName = "Task : find target";
		nodeType = NodeType::SpecializedNode;
	}
	virtual bool run() override {
		_getch();
		return playerAI->findClosestTarget();
	}
};

class TurnTowardTargetTask : public Node {
private:
	Player* playerAI;

public:
	TurnTowardTargetTask(Player* _playerAI) : playerAI(_playerAI) {
		nodeName = "Task : turn toward target";
		nodeType = NodeType::SpecializedNode;
	}
	virtual bool run() override {
		_getch();
		playerAI->turnTowardClosestTarget();
		return true;
	}
};

class AdvanceWhileNotBlockedTask : public Node {
private:
	Player* playerAI;

public:
	AdvanceWhileNotBlockedTask(Player* _playerAI) : playerAI(_playerAI) {
		nodeName = "Task : advance while not blocked";
		nodeType = NodeType::SpecializedNode;
	}
	virtual bool run() override {
		_getch();
		while (playerAI->canAdvance().first && playerAI->hasNotAttainedObjective()) {
			_getch();
			playerAI->advance();
		}
		return true;
	}
};

class BlockedByTargetTask : public Node {
private:
	Player* playerAI;

public:
	BlockedByTargetTask(Player* _playerAI) : playerAI(_playerAI) {
		nodeName = "Task : blocked by target?";
		nodeType = NodeType::SpecializedNode;
	}
	virtual bool run() override {
		_getch();
		return (playerAI->canAdvance().second == SquareType::Target);
	}
};

class AdvcanceMaxAttainedTask : public Node {
private:
	Player* playerAI;

public:
	AdvcanceMaxAttainedTask(Player* _playerAI) : playerAI(_playerAI) {
		nodeName = "Task : AdvanceAttained?";
		nodeType = NodeType::SpecializedNode;
	}
	virtual bool run() override {
		_getch();
		return (!playerAI->hasNotAttainedObjective());
	}
};

class ChooseDirectionInFrontOfWallTask : public Node {
private:
	Player* playerAI;

public:
	ChooseDirectionInFrontOfWallTask(Player* _playerAI) : playerAI(_playerAI) {
		nodeName = "Task : choose direction in front of wall";
		nodeType = NodeType::SpecializedNode;
	}
	virtual bool run() override {
		_getch();
		return playerAI->turnForWall();
	}
};

class AdvanceOnlyOneSquareTask : public Node {
private:
	Player* playerAI;

public:
	AdvanceOnlyOneSquareTask(Player* _playerAI) : playerAI(_playerAI) {
		nodeName = "Task : advance one square";
		nodeType = NodeType::SpecializedNode;
	}
	virtual bool run() override {
		_getch();
		playerAI->advance();
		return true;
	}
};