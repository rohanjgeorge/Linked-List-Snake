#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class GameplayUIController
{
private:
	sf::RenderWindow* game_window;
	const sf::Color gameplay_bg_color = sf::Color::Blue;

public:
	GameplayUIController(sf::RenderWindow* window);

	void show();
	void update();
};

