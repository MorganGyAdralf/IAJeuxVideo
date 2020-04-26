#pragma once
#include <random>
#include <tuple>
#include <assert.h>
#include <iostream>
#include <math.h>
#include "GraphicGridWorld.h"

enum class Direction {	// Enum avec les différentes directions dans lesquelles le joueur peut être tourné
	North,
	East,
	South,
	West
};

class GameWorld {
private:
	unsigned int width_;
	unsigned int height_;
	unsigned int targetsDestroyed_ = 0;
	unsigned int nbOfPlayers_ = 0;
	const unsigned int nbOfWalls_ = 10;
	const unsigned int nbOfTargets_ = 3;
	const unsigned int nbOfTraps_ = 0;
	vector<vector<SquareType>> gridWorld_;
	GraphicGridWorld* graphicWorld_;
	sf::RenderWindow* worldWindow_;
	bool gameIsOn_ = true;

public:
	GameWorld(unsigned int p_w, unsigned int p_h);
	~GameWorld();
	void updateGraphicalWorld() const;
	SquareType getWorldSquare(unsigned int p_x, unsigned int p_y) const;
	pair<unsigned int, unsigned int> spawnPlayer();
	pair<bool, SquareType> playerCanAdvance(pair<unsigned int, unsigned int> p_playerPosition, Direction p_forward) const;
	pair<unsigned int, unsigned int> advancePlayer(pair<unsigned int, unsigned int> p_playerPosition, Direction p_forward);
	pair<unsigned int, unsigned int> computeNewPosition(unsigned int p_x, unsigned int p_y, Direction p_forward) const;
	void attackTarget(pair<unsigned int, unsigned int> p_playerPosition, Direction p_forward);
	bool gameIsOngoing();
	pair<unsigned int, unsigned int> findclosestTarget(pair<unsigned int, unsigned int> p_playerPosition) const;

};

