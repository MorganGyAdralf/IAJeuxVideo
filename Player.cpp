#include "Player.h"

Player::Player(GameWorld* world) : currentWorld(world) {
	playerPosition = currentWorld->spawnPlayer();
	playerDestination = playerPosition;
	playerLookingDirection = Direction::North;
}

bool Player::attackAMeleeTarget() {
	if (currentWorld->playerCanAdvance(playerPosition, Direction::East).second == SquareType::Target) {
		currentWorld->attackTarget(playerPosition, Direction::East);
		cout << "PLAYER:: j'ai attaque a l'est" << endl;
		return true;
	}
	else if (currentWorld->playerCanAdvance(playerPosition, Direction::North).second == SquareType::Target) {
		currentWorld->attackTarget(playerPosition, Direction::North);
		cout << "PLAYER:: j'ai attaque au nord" << endl;
		return true;
	}
	else if (currentWorld->playerCanAdvance(playerPosition, Direction::South).second == SquareType::Target) {
		currentWorld->attackTarget(playerPosition, Direction::South);
		cout << "PLAYER:: j'ai attaque au sud" << endl;
		return true;
	}
	else if (currentWorld->playerCanAdvance(playerPosition, Direction::West).second == SquareType::Target) {
		currentWorld->attackTarget(playerPosition, Direction::West);
		cout << "PLAYER:: j'ai attaque a l'ouest" << endl;
		return true;
	}
	else {
		cout << "PLAYER:: pas de cible a attaquer" << endl;
		return false;
	}
}

bool Player::findClosestTarget() {
	playerDestination = currentWorld->findclosestTarget(playerPosition);
	if (playerDestination == playerPosition) {
		cout << "PLAYER:: pas de cible trouvee" << endl;
		return false;
	}
	cout << "PLAYER:: cible trouvee en " << playerDestination.first << " " << playerDestination .second << endl;
	return true;
}

void Player::turnTowardClosestTarget() {
	int xDist = playerDestination.first - playerPosition.first;
	int yDist = playerDestination.second - playerPosition.second;
	if (abs(xDist) >= abs(yDist)) {
		if (xDist > 0) {
			playerLookingDirection = Direction::East;
			cout << "PLAYER:: je me tourne vers l'est" << endl;
		}
		else {
			playerLookingDirection = Direction::West;
			cout << "PLAYER:: je me tourne vers l'ouest" << endl;
		}
	}
	else {
		if (yDist > 0) {
			playerLookingDirection = Direction::North;
			cout << "PLAYER:: je me tourne vers le nord" << endl;
		}
		else {
			playerLookingDirection = Direction::South;
			cout << "PLAYER:: je me tourne vers le sud" << endl;
		}
	}
}

pair<bool, SquareType> Player::canAdvance() const {
	return currentWorld->playerCanAdvance(playerPosition, playerLookingDirection);
}

void Player::advance() {
	playerPosition = currentWorld->advancePlayer(playerPosition, playerLookingDirection);
	cout << "PLAYER:: j'ai avance d'une case" << endl;
}

bool Player::turnForWall() {
	if (playerLookingDirection == Direction::East || playerLookingDirection == Direction::West) {
		if (currentWorld->playerCanAdvance(playerPosition, Direction::North).first) {
			playerLookingDirection = Direction::North;
			cout << "PLAYER:: je me tourne vers le nord" << endl;
		}
		else if (currentWorld->playerCanAdvance(playerPosition, Direction::South).first) {
			playerLookingDirection = Direction::South;
			cout << "PLAYER:: je me tourne vers le sud" << endl;
		}
		else {
			cout << "PLAYER:: pas moyen de contourner le mur" << endl;
			return false;
		}
	}
	else {
		if (currentWorld->playerCanAdvance(playerPosition, Direction::East).first) {
			playerLookingDirection = Direction::East;
			cout << "PLAYER:: je me tourne vers l'est" << endl;
		}
		else if (currentWorld->playerCanAdvance(playerPosition, Direction::West).first) {
			playerLookingDirection = Direction::West;
			cout << "PLAYER:: je me tourne vers l'ouest" << endl;
		}
		else {
			cout << "PLAYER:: pas moyen de contourner le mur" << endl;
			return false;
		}
	}
	return true;
}

bool Player::hasNotAttainedObjective() {
	int distRest;
	if (playerLookingDirection == Direction::East || playerLookingDirection == Direction::West)
		distRest = abs(playerDestination.first - playerPosition.first);
	else
		distRest = abs(playerDestination.second - playerPosition.second);
	cout << "PLAYER:: distance restante a l'objectif : " << distRest << endl;
	return (distRest > 0);
}

bool Player::gameIsOn() {
	return currentWorld->gameOngoing();
}