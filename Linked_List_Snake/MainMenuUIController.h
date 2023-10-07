#pragma once
#include <SFML/Graphics.hpp>

class MainMenuUIController
{
private:
	sf::RenderWindow* game_window;

	sf::Texture background_texture;
	sf::Sprite background_sprite;
	sf::Texture play_button_texture;
	sf::Sprite play_button_sprite;
	sf::Texture instructions_button_texture;
	sf::Sprite instructions_button_sprite;
	sf::Texture quit_button_texture;
	sf::Sprite quit_button_sprite;

	const float button_width = 400.f;
	const float button_height = 140.f;

	void setBackgroundImage();
	void initializeButtons();
	bool loadButtonTexturesFromFile();
	void setButtonSprites();
	void scaleButttons();
	void positionButtons();
	void handleButtonInteractions(sf::Vector2f mouse_position);

public:
	MainMenuUIController(sf::RenderWindow* window);

	void show();
	void update();
};
