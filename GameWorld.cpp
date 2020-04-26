#include "GameWorld.h"

GameWorld::GameWorld(unsigned int p_w, unsigned int p_h) : width_(p_w), height_(p_h) {
	unsigned int t_x, t_y, t_numberPlaced;
	vector<SquareType> t_tmp;

	t_tmp.reserve(height_);
	gridWorld_.reserve(width_);
	for (t_x = 0; t_x < width_; t_x++) {
		t_tmp.clear();
		for (t_y = 0; t_y < height_; t_y++)
			t_tmp.push_back(SquareType::Empty);
		gridWorld_.push_back(t_tmp);
	}

	random_device t_rd;
	mt19937 t_gen(t_rd());
	uniform_int_distribution<> t_disX(0, width_ - 1);
	uniform_int_distribution<> t_disY(0, height_ - 1);

	t_numberPlaced = 0;
	while (t_numberPlaced < nbOfWalls_) {
		t_x = t_disX(t_gen);
		t_y = t_disY(t_gen);
		if (gridWorld_[t_x][t_y] == SquareType::Empty) {
			gridWorld_[t_x][t_y] = SquareType::Wall;
			++t_numberPlaced;
		}
	}

	t_numberPlaced = 0;
	while (t_numberPlaced < nbOfTargets_) {
		t_x = t_disX(t_gen);
		t_y = t_disY(t_gen);
		if (gridWorld_[t_x][t_y] == SquareType::Empty) {
			gridWorld_[t_x][t_y] = SquareType::Target;
			++t_numberPlaced;
		}
	}

	t_numberPlaced = 0;
	while (t_numberPlaced < nbOfTraps_) {
		t_x = t_disX(t_gen);
		t_y = t_disY(t_gen);
		if (gridWorld_[t_x][t_y] == SquareType::Empty) {
			gridWorld_[t_x][t_y] = SquareType::Trap;
			++t_numberPlaced;
		}
	}

	worldWindow_ = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Grid World");
	graphicWorld_ = new GraphicGridWorld(width_, height_, worldWindow_);
	updateGraphicalWorld();
}

GameWorld::~GameWorld() {
	delete(graphicWorld_);
	delete(worldWindow_);
	for (unsigned int t_x = 0; t_x < width_; t_x++)
		gridWorld_[t_x].clear();
	gridWorld_.clear();
}

void GameWorld::updateGraphicalWorld() const {
	worldWindow_->clear(sf::Color(125, 125, 125));
	graphicWorld_->updateGridWorld(worldWindow_, gridWorld_);
	worldWindow_->display();
}

SquareType GameWorld::getWorldSquare(unsigned int p_x, unsigned int p_y) const {
	assert(p_x >= 0 && p_x < width_);
	assert(p_y >= 0 && p_y < height_);
	if (p_x < 0) p_x = 0;
	if (p_x >= width_) p_x = width_ - 1;
	if (p_y < 0) p_y = 0;
	if (p_y >= height_) p_y = height_ - 1;

	return gridWorld_[p_x][p_y];
}

pair<unsigned int, unsigned int> GameWorld::spawnPlayer() {
	random_device t_rd;
	mt19937 t_gen(t_rd());
	uniform_int_distribution<> t_posX(0, width_ - 1);
	uniform_int_distribution<> t_posY(0, height_ - 1);
	unsigned int t_x, t_y;
	while (true) {
		t_x = t_posX(t_gen);
		t_y = t_posY(t_gen);
		if (gridWorld_[t_x][t_y] == SquareType::Empty) {
			gridWorld_[t_x][t_y] = SquareType::Player;
			break;
		}
	}
	++nbOfPlayers_;
	updateGraphicalWorld();
	return make_pair(t_x, t_y);
}

pair<bool, SquareType> GameWorld::playerCanAdvance(pair<unsigned int, unsigned int> p_playerPosition, Direction p_forward) const {
	pair<unsigned int, unsigned int> t_newPosition = computeNewPosition(p_playerPosition.first, p_playerPosition.second, p_forward);
	if (t_newPosition.first >= 0 && t_newPosition.second >= 0 && t_newPosition.first < width_ && t_newPosition.second < height_) {
		return make_pair(gridWorld_[t_newPosition.first][t_newPosition.second] == SquareType::Empty || gridWorld_[t_newPosition.first][t_newPosition.second] == SquareType::Trap,
			gridWorld_[t_newPosition.first][t_newPosition.second]);
	}
	else
		return make_pair(false, SquareType::Border);
}

pair<unsigned int, unsigned int> GameWorld::advancePlayer(pair<unsigned int, unsigned int> p_playerPosition, Direction p_forward) {
	pair<unsigned int, unsigned int> t_newPosition = computeNewPosition(p_playerPosition.first, p_playerPosition.second, p_forward);
	if (gridWorld_[t_newPosition.first][t_newPosition.second] == SquareType::Trap) {
		cout << "GAMELOG:: YOU DIED!" << endl;
		gameIsOn_ = false;
		return p_playerPosition;
	}
	else {
		gridWorld_[p_playerPosition.first][p_playerPosition.second] = SquareType::Empty;
		gridWorld_[t_newPosition.first][t_newPosition.second] = SquareType::Player;
		updateGraphicalWorld();
		return t_newPosition;
	}
}

// On considère un tableau déployé comme un plan2D : les x augmentent vers l'est et les y vers le nord
pair<unsigned int, unsigned int> GameWorld::computeNewPosition(unsigned int p_x, unsigned int p_y, Direction p_forward) const {
	unsigned int t_xRet = p_x, t_yRet = p_y;
	switch (p_forward) {
	case Direction::North:
		++t_yRet;
		break;

	case Direction::East:
		++t_xRet;
		break;

	case Direction::South:
		--t_yRet;
		break;

	case Direction::West:
		--t_xRet;
		break;
	}
	return make_pair(t_xRet, t_yRet);
}

void GameWorld::attackTarget(pair<unsigned int, unsigned int> p_playerPosition, Direction p_forward) {
	pair<unsigned int, unsigned int> t_targetPosition = computeNewPosition(p_playerPosition.first, p_playerPosition.second, p_forward);
	if (gridWorld_[t_targetPosition.first][t_targetPosition.second] == SquareType::Target) {
		gridWorld_[t_targetPosition.first][t_targetPosition.second] = SquareType::Empty;
		++targetsDestroyed_;
		cout << "GAMELOG:: One more target destroyed!" << endl;
		updateGraphicalWorld();
	}
	else {
		cout << "GAMELOG:: You cannot attack there!" << endl;
	}
}

bool GameWorld::gameIsOngoing() {	// Fonction qui vérifie si les conditions de victoire et de défaites sont remplies
	if (targetsDestroyed_ == nbOfTargets_) {
		gameIsOn_ = false;
		cout << "GAMELOG:: You destroyed all targets, victory to You!" << endl;
	}
	if (nbOfPlayers_ == 0) {
		gameIsOn_ = false;
		cout << "GAMELOG:: No player in this game!" << endl;
	}
	return gameIsOn_;
}

pair<unsigned int, unsigned int> GameWorld::findclosestTarget(pair<unsigned int, unsigned int> p_playerPosition) const {
	pair<unsigned int, unsigned int> t_closestTarget = p_playerPosition;
	unsigned int t_minDist = 100000;
	unsigned int t_currentDist, t_x, t_y;
	for (t_x = 0; t_x < width_; ++t_x) {
		for (t_y = 0; t_y < height_; ++t_y) {
			if (gridWorld_[t_x][t_y] == SquareType::Target) {
				t_currentDist = (unsigned int)(pow(t_x - p_playerPosition.first, 2) + pow(t_y - p_playerPosition.second, 2));
				if (t_currentDist < t_minDist) {
					t_minDist = t_currentDist;
					t_closestTarget.first = t_x;
					t_closestTarget.second = t_y;
				}
			}
		}
	}
	return t_closestTarget;
}