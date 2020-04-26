#include "Tree.h"

Tree::Tree(Player* p_player) : treePlayer_(p_player) {
	root_ = new Sequence;
	Sequence* t_moveToTarget = new Sequence;
	Sequence* t_dodgeWall = new Sequence;

	Selector* t_hitTarget = new Selector;
	Selector* t_blocked = new Selector;

	AttackTargetTask* t_attackTask = new AttackTargetTask(treePlayer_);
	FindTargetTask* t_findTargetTask = new FindTargetTask(treePlayer_);
	TurnTowardTargetTask* t_turnTowardTargetTask = new TurnTowardTargetTask(treePlayer_);
	AdvanceWhileNotBlockedTask* t_advanceWhileNotBlockedTask = new AdvanceWhileNotBlockedTask(treePlayer_);
	BlockedByTargetTask* t_blockedByTargetTask = new BlockedByTargetTask(treePlayer_);
	AdvanceMaxAttainedTask* t_advcanceMaxAttainedTask = new AdvanceMaxAttainedTask(treePlayer_);
	ChooseDirectionInFrontOfWallTask* t_chooseDirection = new ChooseDirectionInFrontOfWallTask(treePlayer_);
	AdvanceOnlyOneSquareTask* t_advanceOnlyOneSquareTask = new AdvanceOnlyOneSquareTask(treePlayer_);

	root_->addChild(t_hitTarget);

	t_hitTarget->addChild(t_attackTask);
	t_hitTarget->addChild(t_moveToTarget);

	t_moveToTarget->addChild(t_findTargetTask);
	t_moveToTarget->addChild(t_turnTowardTargetTask);
	t_moveToTarget->addChild(t_advanceWhileNotBlockedTask);
	t_moveToTarget->addChild(t_blocked);

	t_blocked->addChild(t_blockedByTargetTask);
	t_blocked->addChild(t_advcanceMaxAttainedTask);
	t_blocked->addChild(t_dodgeWall);

	t_dodgeWall->addChild(t_chooseDirection);
	t_dodgeWall->addChild(t_advanceOnlyOneSquareTask);
}

Tree::~Tree() {
	delete(root_);
}

void Tree::run() const {
	while (treePlayer_->gameIsOn()) {
		cout << "---------- nouvelle passe ----------" << endl;
		root_->run();
	}
}