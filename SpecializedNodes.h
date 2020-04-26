#pragma once
#include "Node.h"
#include "Player.h"

class AttackTargetTask : public Node {	// Tache qui essaye d'attaquer les quatres cases autour du joueur
private:
	Player* playerAI_;

public:
	AttackTargetTask(Player* p_playerAI) : playerAI_(p_playerAI) {
		nodeName_ = "Task : attack target";
		nodeType_ = NodeType::SpecializedNode;
	}

	~AttackTargetTask() {
		delete(playerAI_);
	}

	virtual NodeReturnType run() override {
		_getch();
		bool t_ret = playerAI_->attackAMeleeTarget();
		if (t_ret == true)
			return NodeReturnType::Succes;
		else
			return NodeReturnType::Failure;
	}
};

class FindTargetTask : public Node {	// Tache qui essaye de trouver la cible la plus proche
private:
	Player* playerAI_;

public:
	FindTargetTask(Player* p_playerAI) : playerAI_(p_playerAI) {
		nodeName_ = "Task : find target";
		nodeType_ = NodeType::SpecializedNode;
	}

	~FindTargetTask() {
		delete(playerAI_);
	}

	virtual NodeReturnType run() override {
		_getch();
		bool t_ret = playerAI_->findClosestTarget();
		if (t_ret == true)
			return NodeReturnType::Succes;
		else
			return NodeReturnType::Failure;
	}
};

class TurnTowardTargetTask : public Node {	// Tache qui tourne le joueur dans la direction de sa cible
private:
	Player* playerAI_;

public:
	TurnTowardTargetTask(Player* p_playerAI) : playerAI_(p_playerAI) {
		nodeName_ = "Task : turn toward target";
		nodeType_ = NodeType::SpecializedNode;
	}

	~TurnTowardTargetTask() {
		delete(playerAI_);
	}

	virtual NodeReturnType run() override {
		_getch();
		playerAI_->turnTowardClosestTarget();
		return NodeReturnType::Succes;
	}
};

class AdvanceWhileNotBlockedTask : public Node {	// Tache qui fait avancer le joueur tant qu'il n'est pas bloqué ou n'a pas atteint sa cible
private:
	Player* playerAI_;
	unsigned int tickCounter_;	// Compteur pour simuler le fait que la tache dure plus qu'une frame
	const unsigned int maxCounter_ = 3;	// Maximum de ticks avant que la boucle ne renvois Running

public:
	AdvanceWhileNotBlockedTask(Player* p_playerAI) : playerAI_(p_playerAI) {
		nodeName_ = "Task : advance while not blocked";
		nodeType_ = NodeType::SpecializedNode;
	}

	~AdvanceWhileNotBlockedTask() {
		delete(playerAI_);
	}

	virtual NodeReturnType run() override {
		_getch();
		wasRunning_ = false;
		tickCounter_ = 0;
		while (playerAI_->canAdvance().first && playerAI_->hasNotAttainedObjective() && tickCounter_ < maxCounter_) {
			_getch();
			playerAI_->advance();
			++tickCounter_;
		}
		if (tickCounter_ >= maxCounter_) {
			wasRunning_ = true;
			cout << "TASK:: pas eu le temps de finir avant la prochaine frame, task running" << endl;
			return NodeReturnType::Running;
		}
		else
			return NodeReturnType::Succes;
	}
};

class BlockedByTargetTask : public Node {	// Tache qui regarde si le joueur est bloqué par une cible
private:
	Player* playerAI_;

public:
	BlockedByTargetTask(Player* p_playerAI) : playerAI_(p_playerAI) {
		nodeName_ = "Task : blocked by target?";
		nodeType_ = NodeType::SpecializedNode;
	}

	~BlockedByTargetTask() {
		delete(playerAI_);
	}

	virtual NodeReturnType run() override {
		_getch();
		bool t_ret = (playerAI_->canAdvance().second == SquareType::Target);
		if (t_ret == true)
			return NodeReturnType::Succes;
		else
			return NodeReturnType::Failure;
	}
};

class AdvanceMaxAttainedTask : public Node {	// Tache qui vérifie si le joueur est bloqué car il a atteint son objectif
private:
	Player* playerAI_;

public:
	AdvanceMaxAttainedTask(Player* p_playerAI) : playerAI_(p_playerAI) {
		nodeName_ = "Task : AdvanceAttained?";
		nodeType_ = NodeType::SpecializedNode;
	}

	~AdvanceMaxAttainedTask() {
		delete(playerAI_);
	}

	virtual NodeReturnType run() override {
		_getch();
		bool t_ret = playerAI_->hasNotAttainedObjective();
		if (t_ret == false)
			return NodeReturnType::Succes;
		else
			return NodeReturnType::Failure;
	}
};

class ChooseDirectionInFrontOfWallTask : public Node {	// Tache qui essaye de changer la direction du joueur face à un mur
private:
	Player* playerAI_;

public:
	ChooseDirectionInFrontOfWallTask(Player* p_playerAI) : playerAI_(p_playerAI) {
		nodeName_ = "Task : choose direction in front of wall";
		nodeType_ = NodeType::SpecializedNode;
	}

	~ChooseDirectionInFrontOfWallTask() {
		delete(playerAI_);
	}

	virtual NodeReturnType run() override {
		_getch();
		bool t_ret = playerAI_->turnForWall();
		if (t_ret == true)
			return NodeReturnType::Succes;
		else
			return NodeReturnType::Failure;
	}
};

class AdvanceOnlyOneSquareTask : public Node {	// Tache qui avance d'une seule case, pour contourner un mur
private:
	Player* playerAI_;

public:
	AdvanceOnlyOneSquareTask(Player* p_playerAI) : playerAI_(p_playerAI) {
		nodeName_ = "Task : advance one square";
		nodeType_ = NodeType::SpecializedNode;
	}

	~AdvanceOnlyOneSquareTask() {
		delete(playerAI_);
	}

	virtual NodeReturnType run() override {
		_getch();
		playerAI_->advance();
		return NodeReturnType::Succes;
	}
};