// IAJeuxVideo.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GraphicGridWorld.h"
#include "GraphicAgent.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Behavior Tree");
    sf::RenderWindow window2(sf::VideoMode(1000, 1000), "Grid World");

    GraphicGridWorld gridWorld(10, 10, window2);
    GraphicAgent agent(gridWorld);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
  
    while (window2.isOpen())
    {
        sf::Event event;
        while (window2.pollEvent(event))
        {
            if (agent.GetCurrentAgentPosition() > 0 && agent.GetCurrentAgentPosition() % gridWorld.GetWorlHeight() != 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                agent.MoveLeft();
            }
            else if (agent.GetCurrentAgentPosition() < gridWorld.GetWorldSize() - 1 && agent.GetCurrentAgentPosition() % gridWorld.GetWorlHeight() != 9 && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                agent.MoveRight();
            }
            else if (agent.GetCurrentAgentPosition() + gridWorld.GetWorlHeight() < gridWorld.GetWorldSize() && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                agent.MoveDown();
            }
            else if (agent.GetCurrentAgentPosition() - gridWorld.GetWorlHeight() >= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                agent.MoveUp();
            }
            if (event.type == sf::Event::Closed)
                window2.close();
        }

        window.clear();
        window.draw(shape);
        window.display();

        window2.clear(sf::Color(125.0f, 125.0f, 125.0f));
        gridWorld.CreateGridWorld(window2);
        agent.CreateAgent(window2, gridWorld);
        window2.display();
    }

    return 0;
}
