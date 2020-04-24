#pragma once
#include <assert.h> 
#include "GameWorld.h"

class Player {
public:
	Player(GameWorld* world);
	Direction getDirection() const {
		return playerLookingDirection;
	}
	void setDirection(Direction newDirection) {
		playerLookingDirection = newDirection;
	}
	bool attackAMeleeTarget();
	bool findClosestTarget();
	void turnTowardClosestTarget();
	pair<bool, SquareType> canAdvance() const;
	void advance();
	bool turnForWall();
	bool hasNotAttainedObjective();
	bool gameIsOn();

private:
	GameWorld* currentWorld;
	pair<int, int> playerPosition;
	pair<int, int> playerDestination;
	Direction playerLookingDirection;
};

