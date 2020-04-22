#pragma once
#include <assert.h> 
#include "GameWorld.h"


class Player {
public:
	Player(GameWorld& world);
	Direction getDirection() const {
		return playerLookingDirection;
	}
	void setDirection(Direction newDirection) {
		playerLookingDirection = newDirection;
	}

private:
	GameWorld& currentWorld;
	pair<int, int> playerPosition;
	Direction playerLookingDirection;
};

