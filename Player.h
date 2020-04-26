#pragma once
#include <assert.h> 
#include "GameWorld.h"

class Player {
private:
	GameWorld* currentWorld_;
	pair<int, int> playerPosition_;
	pair<int, int> playerDestination_;
	Direction playerLookingDirection_;

public:
	Player(GameWorld* p_world);
	~Player();
	pair<bool, SquareType> canAdvance() const;
	bool attackAMeleeTarget() const;
	bool hasNotAttainedObjective() const;
	bool gameIsOn() const;
	bool findClosestTarget();
	void turnTowardClosestTarget();
	void advance();
	bool turnForWall();
};

