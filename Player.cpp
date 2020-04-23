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

}