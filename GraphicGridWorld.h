#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

enum class SquareType {	// Une enum pour les différents types de cases
	Empty,
	Wall,
	Target,
	Trap,
	Border,
	Player
};

class GraphicGridWorld {
private:
	unsigned int rows_;
	unsigned int columns_;
	float squareWidth_;
	float squareHeight_;
	vector<sf::RectangleShape> gridWorld_;
	
public:
	GraphicGridWorld(unsigned int p_cols, unsigned int p_rows, sf::RenderWindow* p_window);
	~GraphicGridWorld();
	void updateGridWorld(sf::RenderWindow* p_window, vector<vector<SquareType>> p_gridWorld);
};