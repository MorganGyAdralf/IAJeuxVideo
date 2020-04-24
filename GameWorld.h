#pragma once
#include <random>
#include <tuple>
#include <assert.h>
#include <iostream>
#include <math.h>
#include "GraphicGridWorld.h"
#include "GraphicAgent.h"

using namespace std;

enum class Direction {
	North,
	East,
	South,
	West
};

class GameWorld {
public:
	GameWorld(int w, int h);
	~GameWorld() {}
	const int getWorldwidth() const {
		return width;
	}
	const int getWorldheight() const  {
		return height;
	}
	SquareType getWorldSquare(int x, int y) const;
	void setWorldSquare(int x, int y, SquareType newType);
	pair<int, int> spawnPlayer();
	pair<bool, SquareType> playerCanAdvance(pair<int, int> playerPosition, Direction forward) const;
	pair<int, int> advancePlayer(pair<int, int> playerPosition, Direction forward);
	pair<int, int> computeNewPosition(int x, int y, Direction forward) const;
	void attackTarget(pair<int, int> playerPosition, Direction forward);
	bool gameOngoing();
	pair<int, int> findclosestTarget(pair<int, int> playerPosition) const;
	void updateGraphicalWorld();

private:
	int width;
	int height;
	int targetsDestroyed = 0;
	int nbOfPlayers = 0;
	const int nbOfWalls = 10;
	const int nbOfTargets = 3;
	const int nbOfTraps = 0;
	vector<vector<SquareType>> gridWorld;
	GraphicGridWorld graphicWorld;
	bool gameIsOn = true;
};

