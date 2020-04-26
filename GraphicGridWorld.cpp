#include "GraphicGridWorld.h"

GraphicGridWorld::GraphicGridWorld(unsigned int p_cols, unsigned int p_rows, sf::RenderWindow* p_window) : columns_(p_cols), rows_(p_rows) {
	squareWidth_ = (p_window->getSize().x - 5.0f * 2) / columns_ - 1.0f;
	squareHeight_ = (p_window->getSize().y - 5.0f * 2) / rows_ - 1.0f;
	unsigned int t_row, t_col;
	sf::RectangleShape t_rect;
	gridWorld_.reserve(columns_ * rows_);
	for (t_row = 0; t_row < rows_; t_row++) {
		for (t_col = 0; t_col < columns_; t_col++) {
			t_rect.setSize(sf::Vector2f(squareWidth_, squareHeight_));
			t_rect.setPosition(sf::Vector2f((squareWidth_ + 1.0f) * t_col + 5.0f,
				p_window->getSize().y - 5.0f - (squareHeight_ + 1.0f) * (t_row + 1)));
			t_rect.setFillColor(sf::Color::Black);
			gridWorld_.push_back(t_rect);
		}
	}
}

GraphicGridWorld::~GraphicGridWorld() {
	gridWorld_.clear();
}

void GraphicGridWorld::updateGridWorld(sf::RenderWindow* p_window, std::vector<std::vector<SquareType>> p_gridWorld) {
	unsigned int index = 0, y, x;
	for (y = 0; y < rows_; y++) {
		for (x = 0; x < columns_; x++) {
			switch (p_gridWorld[x][y]) {
			case SquareType::Empty:
				gridWorld_[index].setFillColor(sf::Color::Black);
				break;

			case SquareType::Wall:
				gridWorld_[index].setFillColor(sf::Color::White);
				break;

			case SquareType::Target:
				gridWorld_[index].setFillColor(sf::Color::Blue);
				break;

			case SquareType::Trap:
				gridWorld_[index].setFillColor(sf::Color::Red);
				break;

			case SquareType::Player:
				gridWorld_[index].setFillColor(sf::Color::Green);
				break;
			}
			p_window->draw(gridWorld_[index]);
			++index;
		}
	}
}
