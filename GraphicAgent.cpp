#include <SFML/Graphics.hpp>
#include "GraphicGridWorld.h"
#include "GraphicAgent.h"
#include <iostream>

GraphicAgent::GraphicAgent(GraphicGridWorld world) {
	this->m_currentAgentPosition = 0;
	this->m_squareSize = world.GetSquareSize();
	this->m_agent = sf::CircleShape(m_squareSize / 2, 3);
	this->m_agent.setFillColor(sf::Color::Green);
	this->m_agent.setPosition(sf::Vector2f(world.GetCasePosition(this->m_currentAgentPosition).x, world.GetCasePosition(this->m_currentAgentPosition).y + (this->m_squareSize - this->m_agent.getLocalBounds().height) / 2));
	this->m_worldSize = world.GetWorlHeight();
}

void GraphicAgent::CreateAgent(sf::RenderWindow& window, GraphicGridWorld world) {
	this->m_agent.setPosition(sf::Vector2f(world.GetCasePosition(this->m_currentAgentPosition).x, world.GetCasePosition(this->m_currentAgentPosition).y + (this->m_squareSize - this->m_agent.getLocalBounds().height) / 2));
	window.draw(this->m_agent);
}

int GraphicAgent::GetAgentPosition() {
	return m_currentAgentPosition;
}

void GraphicAgent::MoveUp() {
	m_currentAgentPosition -= this->m_worldSize;
}

void GraphicAgent::MoveDown() {
	m_currentAgentPosition += this->m_worldSize;
}

void GraphicAgent::MoveLeft() {
	m_currentAgentPosition--;
}

void GraphicAgent::MoveRight() {
	m_currentAgentPosition++;
}

int GraphicAgent::GetCurrentAgentPosition() {
	return m_currentAgentPosition;
}