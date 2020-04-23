#pragma once

enum SquareColor{
	BLACK,
	WHITE,
	RED,
	BLUE
};

struct Square {
	SquareColor color;
	sf::RectangleShape square;
};

class GraphicGridWorld {
private:
	int m_rows;
	int m_cols;
	std::vector<Square> m_gridWorld;
	float m_squareSize;
	
public:
	GraphicGridWorld(int rows, int cols, sf::RenderWindow &window);
	~GraphicGridWorld();
	void CreateGridWorld(sf::RenderWindow &window);
	sf::Vector2f GetCasePosition(int index);
	float GetSquareSize();
	int GetWorlHeight();
	int GetWorldSize();
};