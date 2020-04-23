#include <SFML/Graphics.hpp>
#include "GraphicGridWorld.h"
#include <iostream>
#include <vector>

GraphicGridWorld::GraphicGridWorld(int rows, int cols, sf::RenderWindow &window) : m_rows(rows), m_cols(cols) {
	int index = 0;
	float space = 5.0f;
	int walls[] = { 2, 3, 4, 5, 6, 10, 12, 18, 20, 22, 24, 26, 28, 34, 36, 40, 41, 42, 46, 47, 52, 54, 64, 65, 66, 67, 49, 59, 70, 71, 72, 69, 84, 86, 87, 88, 91, 92, 94, 98 };
	int traps[] = { 27, 30, 39, 43, 79, 97};
	int targets[] = {9, 37, 44, 70, 90, 96};
	m_squareSize = window.getSize().y / m_rows - 5.0f;

	// Draw Grid World
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			Square rect;
			rect.color = BLACK;
			rect.square.setSize(sf::Vector2f(m_squareSize, m_squareSize));
			rect.square.setFillColor(sf::Color::Black);
			rect.square.setPosition(sf::Vector2f( ((window.getSize().x - (window.getSize().x / m_cols - 5.0f) * m_cols) / 2) + (rect.square.getGlobalBounds().width + 1.0f) * j,
				((window.getSize().y - (window.getSize().y / m_rows - 5.0f) * m_rows) / 2) + (rect.square.getGlobalBounds().height + 1.0f) * i));
			m_gridWorld.push_back(rect);
			index++;
		}
	}

	// Draw walls
	for (int i = 0; i < sizeof(walls) / sizeof(walls[0]); i++) {
		m_gridWorld.at(walls[i]).color = WHITE;
		m_gridWorld.at(walls[i]).square.setFillColor(sf::Color::White);
	}

	// Draw traps
	for (int i = 0; i < sizeof(traps) / sizeof(traps[0]); i++) {
		m_gridWorld.at(traps[i]).color = RED;
		m_gridWorld.at(traps[i]).square.setFillColor(sf::Color::Red);
	}

	// Draw targets
	for (int i = 0; i < sizeof(targets) / sizeof(targets[0]); i++) {
		m_gridWorld.at(targets[i]).color = BLUE;
		m_gridWorld.at(targets[i]).square.setFillColor(sf::Color::Blue);
	}
}

GraphicGridWorld::~GraphicGridWorld() {

}

void GraphicGridWorld::CreateGridWorld(sf::RenderWindow &window) {
	for (int i = 0; i < m_gridWorld.size(); i++) {
		window.draw(m_gridWorld[i].square);
	}
}

sf::Vector2f GraphicGridWorld::GetCasePosition(int index) {
	return m_gridWorld.at(index).square.getPosition();
}

float GraphicGridWorld::GetSquareSize() {
	return m_squareSize;
}

int GraphicGridWorld::GetWorlHeight() {
	return m_rows;
}

int GraphicGridWorld::GetWorldSize() {
	return m_rows * m_cols;
}
