#include "GameWorld.h"

sf::RenderWindow worldWindow(sf::VideoMode(1000, 1000), "Grid World");	//A voir pour ça

GameWorld::GameWorld(int w, int h) : width(w), height(h) {
	int x, y;
	vector<SquareType> tmp;
	for (x = 0; x < width; x++) {
		tmp.clear();
		for (y = 0; y < height; y++)
			tmp.push_back(SquareType::Empty);
		gridWorld.push_back(tmp);
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> disX(0, width - 1);
	uniform_int_distribution<> disY(0, height - 1);

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
	while (currentTargets < nbOfTargets) {
		x = disX(gen);
		y = disY(gen);
		if (gridWorld[x][y] == SquareType::Empty) {
			gridWorld[x][y] = SquareType::Target;
			++currentTargets;
		}
	}

	int currentTraps = 0;
	while (currentTraps < nbOfTraps) {
		x = disX(gen);
		y = disY(gen);
		if (gridWorld[x][y] == SquareType::Empty) {
			gridWorld[x][y] = SquareType::Trap;
			++currentTraps;
		}
	}

	graphicWorld = GraphicGridWorld(width, height, worldWindow);
	updateGraphicalWorld();
}

void GameWorld::updateGraphicalWorld() {
	worldWindow.clear(sf::Color(125, 125, 125));
	graphicWorld.UpdateGridWorld(worldWindow, gridWorld);
	worldWindow.display();
}

SquareType GameWorld::getWorldSquare(int x, int y) const {
	assert(x >= 0 && x < width);
	assert(y >= 0 && y < height);
	if (x < 0) x = 0;
	if (x >= width) x = width - 1;
	if (y < 0) y = 0;
	if (y >= height) y = height - 1;

	return gridWorld[x][y];
}

void GameWorld::setWorldSquare(int x, int y, SquareType newType) {
	assert(x >= 0 && x < width);
	assert(y >= 0 && y < height);
	if (x < 0) x = 0;
	if (x >= width) x = width - 1;
	if (y < 0) y = 0;
	if (y >= height) y = height - 1;

	gridWorld[x][y] = newType;
}

pair<int, int> GameWorld::spawnPlayer() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> posX(0, width - 1);
	uniform_int_distribution<> posY(0, height - 1);
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
	updateGraphicalWorld();
	return make_pair(x, y);
}

pair<bool, SquareType> GameWorld::playerCanAdvance(pair<int, int> playerPosition, Direction forward) const {
	pair<int, int> newPosition = computeNewPosition(playerPosition.first, playerPosition.second, forward);
	if (newPosition.first >= 0 && newPosition.second >= 0 && newPosition.first < width && newPosition.second < height) {
		SquareType tmp = gridWorld[newPosition.first][newPosition.second];
		bool tmp2 = gridWorld[newPosition.first][newPosition.second] == SquareType::Empty || gridWorld[newPosition.first][newPosition.second] == SquareType::Trap;


		return make_pair(gridWorld[newPosition.first][newPosition.second] == SquareType::Empty || gridWorld[newPosition.first][newPosition.second] == SquareType::Trap,
			gridWorld[newPosition.first][newPosition.second]);

	}
	else
		return make_pair(false, SquareType::Border);
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
		updateGraphicalWorld();
	}
	return newPosition;
}

// On considère un tableau déployé comme un plan2D : les x augmente vers l'est et les y vers le nord
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
	if (gridWorld[targetPosition.first][targetPosition.second] == SquareType::Target) {
		gridWorld[targetPosition.first][targetPosition.second] = SquareType::Empty;
		updateGraphicalWorld();
		++targetsDestroyed;
		cout << "GAMELOG:: One more target destroyed!" << endl;
	}
	else {
		cout << "GAMELOG:: You cannot attack there!" << endl;
	}
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

pair<int, int> GameWorld::findclosestTarget(pair<int, int> playerPosition) const {
	pair<int, int> closestTarget = playerPosition;
	int minDist = 10000000;
	int currentDist;
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			if (gridWorld[x][y] == SquareType::Target) {
				currentDist = (int)(pow(x - playerPosition.first, 2) + pow(y - playerPosition.second, 2));
				if (currentDist < minDist) {
					minDist = currentDist;
					closestTarget.first = x;
					closestTarget.second = y;
				}
			}
		}
	}
	return closestTarget;
}