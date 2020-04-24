#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

enum SquareColor{
	BLACK,
	WHITE,
	RED,
	BLUE, 
	GREEN
};

struct Square {
	SquareColor color;
	sf::RectangleShape square;
};

enum class SquareType {
	Empty,
	Wall,
	Target,
	Trap,
	Border,
	Player
};

class GraphicGridWorld {
private:
	int m_rows;
	int m_cols;
	std::vector<Square> m_gridWorld;
	float m_squarewidth;
	float m_squareheight;
	
public:
	GraphicGridWorld();
	GraphicGridWorld(int cols, int rows, sf::RenderWindow& window);
	//GraphicGridWorld(int rows, int cols, sf::RenderWindow &window);
	~GraphicGridWorld();
	void UpdateGridWorld(sf::RenderWindow &window, std::vector<std::vector<SquareType>> gridWorld);
	sf::Vector2f GetCasePosition(int index);
	float GetSquareSize();
	int GetWorlheight();
	int GetWorldSize();
};