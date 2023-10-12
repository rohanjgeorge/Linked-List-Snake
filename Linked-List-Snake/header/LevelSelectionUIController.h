#pragma once
#include <SFML/Graphics.hpp>
#include "../header/IUIController.h"

class LevelSelectionUIController : public IUIController
{
private:
	// Constants:
	const float button_width = 400.f;
	const float button_height = 140.f;

	sf::RenderWindow* game_window;

	// Textures:
	sf::Texture level_one_button_texture;
	sf::Sprite level_one_button_sprite;

	sf::Texture level_two_button_texture;
	sf::Sprite level_two_button_sprite;

	void initializeButtons();
	bool loadButtonTexturesFromFile();
	void setButtonSprites();

	void scaleAllButttons();
	void scaleButton(sf::Sprite* button_to_scale);
	void positionButtons();
	float calculateLeftOffsetForButton();

	void handleButtonInteractions();
	bool clickedButton(sf::Sprite*, sf::Vector2f);

public:
	LevelSelectionUIController();

	void initialize() override;
	void update() override;
	void render() override;
	void show() override;
};