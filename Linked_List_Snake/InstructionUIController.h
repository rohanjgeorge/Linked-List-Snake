#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class InstructionUIController
{
private:
	sf::RenderWindow* game_window;
	const sf::Color instructions_bg_color = sf::Color::Green;

public:
	InstructionUIController(sf::RenderWindow* window);

	void show();
	void update();
};

