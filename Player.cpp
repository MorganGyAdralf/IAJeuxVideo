#include "Player.h"

Player::Player(GameWorld& world) : currentWorld(world) {
	playerPosition = world.spawnPlayer();
	playerLookingDirection = Direction::North;
}