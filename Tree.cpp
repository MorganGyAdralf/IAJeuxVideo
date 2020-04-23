#include "Tree.h"

Tree::Tree(Player* player) {

	Sequence *root = new Sequence;
	Sequence* moveToTarget = new Sequence;
	Sequence* dodgeWall = new Sequence;

	Selector* hitTarget = new Selector;
	Selector* blocked = new Selector;

	AttackTargetTask* attackTask = new AttackTargetTask(player);
	FindTargetTask* findTargetTask = new FindTargetTask(player);
	TurnTowardTargetTask* turnTowardTargetTask = new TurnTowardTargetTask(player);
	AdvanceWhileNotBlockedTask* advanceWhileNotBlockedTask = new AdvanceWhileNotBlockedTask(player);


	BlockedByTargetTask* blockedByTargetTask = new BlockedByTargetTask(player);
	ChooseDirectionInFrontOfWallTask* chooseDirection = new ChooseDirectionInFrontOfWallTask(player);
	AdvanceOnlyOneSquareTask* advanceOnlyOneSquareTask = new AdvanceOnlyOneSquareTask(player);

	root->addChild(hitTarget);

	hitTarget->addChild(attackTask);
	hitTarget->addChild(moveToTarget);

	moveToTarget->addChild(findTargetTask);
	moveToTarget->addChild(turnTowardTargetTask);
	moveToTarget->addChild(advanceWhileNotBlockedTask);
	moveToTarget->addChild(blocked);

	blocked->addChild(blockedByTargetTask);
	blocked->addChild(dodgeWall);

	dodgeWall->addChild(chooseDirection);
	dodgeWall->addChild(advanceOnlyOneSquareTask);

}