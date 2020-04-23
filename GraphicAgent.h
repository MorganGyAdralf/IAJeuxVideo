#pragma once

class GraphicAgent {
private:
	sf::CircleShape m_agent;
	float m_squareSize;
	int m_currentAgentPosition;
	int m_worldSize;

public:
	GraphicAgent(GraphicGridWorld world);
	void CreateAgent(sf::RenderWindow &window, GraphicGridWorld world);
	int GetAgentPosition();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	int GetCurrentAgentPosition();
};
