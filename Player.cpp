#include "Player.h"

Player::Player(GameWorld* world) : currentWorld(world) {
	playerPosition = world->spawnPlayer();
	playerDestination = playerPosition;
	playerLookingDirection = Direction::North;
}

bool Player::attackAMeleeTarget() const {
	if (currentWorld->playerCanAdvance(playerPosition, Direction::East).second == SquareType::Target) {
		currentWorld->attackTarget(playerPosition, Direction::East);
		return true;
	}
	else if (currentWorld->playerCanAdvance(playerPosition, Direction::North).second == SquareType::Target) {
		currentWorld->attackTarget(playerPosition, Direction::North);
		return true;
	}
	else if (currentWorld->playerCanAdvance(playerPosition, Direction::South).second == SquareType::Target) {
		currentWorld->attackTarget(playerPosition, Direction::South);
		return true;
	}
	else if (currentWorld->playerCanAdvance(playerPosition, Direction::West).second == SquareType::Target) {
		currentWorld->attackTarget(playerPosition, Direction::West);
		return true;
	}
	else
		return false;
}

bool Player::findClosestTarget() {
	playerDestination = currentWorld->findclosestTarget(playerPosition);
	if (playerDestination == playerPosition)
		return false;
	return true;
}

void Player::turnTowardClosestTarget() {
	int xDist = playerDestination.first - playerPosition.first;
	int yDist = playerDestination.second - playerPosition.second;
	if (abs(xDist) >= abs(yDist)) {
		if (xDist > 0)
			playerLookingDirection = Direction::East;
		else
			playerLookingDirection = Direction::West;
	}
	else {
		if (yDist > 0)
			playerLookingDirection = Direction::North;
		else
			playerLookingDirection = Direction::South;
	}
}

pair<bool, SquareType> Player::canAdvance() const {
	return currentWorld->playerCanAdvance(playerPosition, playerLookingDirection);
}

void Player::advance() {
	playerPosition = currentWorld->advancePlayer(playerPosition, playerLookingDirection);
}

bool Player::turnForWall() {
	if (playerLookingDirection == Direction::East || playerLookingDirection == Direction::West) {
		if (currentWorld->playerCanAdvance(playerPosition, Direction::North).first)
			playerLookingDirection = Direction::North;
		else if (currentWorld->playerCanAdvance(playerPosition, Direction::South).first)
			playerLookingDirection = Direction::South;
		else return false;
	}
	else {
		if (currentWorld->playerCanAdvance(playerPosition, Direction::East).first)
			playerLookingDirection = Direction::East;
		else if (currentWorld->playerCanAdvance(playerPosition, Direction::West).first)
			playerLookingDirection = Direction::West;
		else return false;
	}
	return true;
}