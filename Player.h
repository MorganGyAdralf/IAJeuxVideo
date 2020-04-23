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
	GameWorld* getWorld() const {
		return currentWorld;
	}
	bool attackAMeleeTarget() const;
	bool findClosestTarget();
	void turnTowardClosestTarget();

private:
	GameWorld* currentWorld;
	pair<int, int> playerPosition;
	pair<int, int> playerDestination;
	Direction playerLookingDirection;
};

