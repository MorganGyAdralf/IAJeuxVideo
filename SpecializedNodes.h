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
	virtual NodeReturnType run() override {
		_getch();
		bool ret = playerAI->attackAMeleeTarget();
		if (ret == true)
			return NodeReturnType::Succes;
		else
			return NodeReturnType::Failure;
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
	virtual NodeReturnType run() override {
		_getch();
		bool ret = playerAI->findClosestTarget();
		if (ret == true)
			return NodeReturnType::Succes;
		else
			return NodeReturnType::Failure;
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
	virtual NodeReturnType run() override {
		_getch();
		playerAI->turnTowardClosestTarget();
		return NodeReturnType::Succes;
	}
};

class AdvanceWhileNotBlockedTask : public Node {
private:
	Player* playerAI;
	int tickCounter;

public:
	AdvanceWhileNotBlockedTask(Player* _playerAI) : playerAI(_playerAI) {
		nodeName = "Task : advance while not blocked";
		nodeType = NodeType::SpecializedNode;
	}
	virtual NodeReturnType run() override {
		_getch();
		wasRunning = false;
		tickCounter = 0;
		while (playerAI->canAdvance().first && playerAI->hasNotAttainedObjective() && tickCounter < 3) {
			_getch();
			playerAI->advance();
			++tickCounter;
		}
		if (tickCounter >= 3) {
			wasRunning = true;
			cout << "TASK:: pas eu le temps de finir avant la prochaine frame, task running" << endl;
			return NodeReturnType::Running;
		}
		else
			return NodeReturnType::Succes;
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
	virtual NodeReturnType run() override {
		_getch();
		bool ret = (playerAI->canAdvance().second == SquareType::Target);
		if (ret == true)
			return NodeReturnType::Succes;
		else
			return NodeReturnType::Failure;
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
	virtual NodeReturnType run() override {
		_getch();
		bool ret = playerAI->hasNotAttainedObjective();
		if (ret == false)
			return NodeReturnType::Succes;
		else
			return NodeReturnType::Failure;
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
	virtual NodeReturnType run() override {
		_getch();
		bool ret = playerAI->turnForWall();
		if (ret == true)
			return NodeReturnType::Succes;
		else
			return NodeReturnType::Failure;
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
	virtual NodeReturnType run() override {
		_getch();
		playerAI->advance();
		return NodeReturnType::Succes;
	}
};