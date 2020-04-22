#pragma once
#include <random>
#include <tuple>
#include <assert.h>
#include <iostream>

using namespace std;

constexpr auto WIDTH = 15;
constexpr auto HEIGHT = 10;

enum class SquareType {
	Empty, 
	Wall,
	Target,
	Trap,
	Player
};

enum class Direction {
	North,
	East,
	South,
	West
};

class GameWorld {
public:
	GameWorld();
	~GameWorld() {}
	const int getWorldWidth() const {
		return WIDTH;
	}
	const int getWorldHeight() const  {
		return HEIGHT;
	}
	SquareType getWorldSquare(int x, int y) const;
	void setWorldSquare(int x, int y, SquareType newType);
	pair<int, int> spawnPlayer();
	pair<bool, SquareType> playerCanAdvance(pair<int, int> playerPosition, Direction forward) const;
	pair<int, int> advancePlayer(pair<int, int> playerPosition, Direction forward);
	pair<int, int> computeNewPosition(int x, int y, Direction forward) const;
	void attackTarget(pair<int, int> playerPosition, Direction forward);
	bool gameOngoing();

private:
	int targetsDestroyed = 0;
	int nbOfPlayers = 0;
	const int nbOfWalls = 15;
	const int nbOfTargets = 3;
	const int nbOfTraps = 5;
	SquareType gridWorld[WIDTH][HEIGHT];
	bool gameIsOn = true;
};

