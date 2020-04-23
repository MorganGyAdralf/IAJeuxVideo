#include "GameWorld.h"


GameWorld::GameWorld() {
	int x, y;
	for (x = 0; x < WIDTH; x++)
		for (y = 0; y < HEIGHT; y++)
			gridWorld[x][y] = SquareType::Empty;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> disX(0, WIDTH);
	uniform_int_distribution<> disY(0, HEIGHT);

	int currentWalls = 0;
	while (currentWalls < nbOfWalls) {
		x = disX(gen);
		y = disY(gen);
		if (gridWorld[x][y] == SquareType::Empty) {
			gridWorld[x][y] = SquareType::Wall;
			++currentWalls;
		}
	}

	int currentTargets = 0;
	while (currentTargets < nbOfWalls) {
		x = disX(gen);
		y = disY(gen);
		if (gridWorld[x][y] == SquareType::Empty) {
			gridWorld[x][y] = SquareType::Target;
			++currentTargets;
		}
	}

	int currentTraps = 0;
	while (currentTraps < nbOfWalls) {
		x = disX(gen);
		y = disY(gen);
		if (gridWorld[x][y] == SquareType::Empty) {
			gridWorld[x][y] = SquareType::Trap;
			++currentTraps;
		}
	}
}

SquareType GameWorld::getWorldSquare(int x, int y) const {
	assert(x >= 0 && x < WIDTH);
	assert(y >= 0 && y < HEIGHT);
	if (x < 0) x = 0;
	if (x >= WIDTH) x = WIDTH - 1;
	if (y < 0) y = 0;
	if (y >= HEIGHT) y = HEIGHT - 1;

	return gridWorld[x][y];
}

void GameWorld::setWorldSquare(int x, int y, SquareType newType) {
	assert(x >= 0 && x < WIDTH);
	assert(y >= 0 && y < HEIGHT);
	if (x < 0) x = 0;
	if (x >= WIDTH) x = WIDTH - 1;
	if (y < 0) y = 0;
	if (y >= HEIGHT) y = HEIGHT - 1;

	gridWorld[x][y] = newType;
}

pair<int, int> GameWorld::spawnPlayer() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> posX(0, WIDTH);
	uniform_int_distribution<> posY(0, HEIGHT);
	int x, y;
	while (true) {
		x = posX(gen);
		y = posY(gen);
		if (gridWorld[x][y] == SquareType::Empty) {
			gridWorld[x][y] = SquareType::Player;
			break;
		}
	}
	++nbOfPlayers;
	return make_pair(x, y);
}

pair<bool, SquareType> GameWorld::playerCanAdvance(pair<int, int> playerPosition, Direction forward) const {
	pair<int, int> newPosition = computeNewPosition(playerPosition.first, playerPosition.second, forward);
	bool canMove = newPosition.first >= 0 && newPosition.second >= 0 && newPosition.first < WIDTH && newPosition.second < HEIGHT &&
		(gridWorld[newPosition.first][newPosition.second] == SquareType::Empty || gridWorld[newPosition.first][newPosition.second] == SquareType::Trap);
	return make_pair(canMove, gridWorld[newPosition.first][newPosition.second]);
}

pair<int, int> GameWorld::advancePlayer(pair<int, int> playerPosition, Direction forward) {
	pair<int, int> newPosition = computeNewPosition(playerPosition.first, playerPosition.second, forward);
	if (gridWorld[newPosition.first][newPosition.second] == SquareType::Trap) {
		cout << "GAMELOG:: YOU DIED!" << endl;
		gameIsOn = false;
	}
	else {
		gridWorld[playerPosition.first][playerPosition.second] = SquareType::Empty;
		gridWorld[newPosition.first][newPosition.second] = SquareType::Player;
	}
	return newPosition;
}

pair<int, int> GameWorld::computeNewPosition(int x, int y, Direction forward) const {
	int xRet = x, yRet = y;
	switch (forward) {
	case Direction::North:
		++yRet;
		break;

	case Direction::East:
		++xRet;
		break;

	case Direction::South:
		--yRet;
		break;

	case Direction::West:
		--xRet;
		break;
	}
	return make_pair(xRet, yRet);
}

void GameWorld::attackTarget(pair<int, int> playerPosition, Direction forward) {
	pair<int, int> targetPosition = computeNewPosition(playerPosition.first, playerPosition.second, forward);
	gridWorld[targetPosition.first][targetPosition.second] = SquareType::Empty;
	++targetsDestroyed;
	cout << "GAMELOG:: One more target destroyed!" << endl;
}

bool GameWorld::gameOngoing() {
	if (targetsDestroyed == nbOfTargets) {
		cout << "GAMELOG:: You destroyed all targets, victory to You!" << endl;
		gameIsOn = false;
	}
	if (nbOfPlayers == 0) {
		cout << "GAMELOG:: No player in this game!" << endl;
		gameIsOn = false;
	}
	return gameIsOn;
}