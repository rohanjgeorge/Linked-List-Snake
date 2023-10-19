#pragma once
#include <SFML/Graphics.hpp>
#include "../header/IUIController.h"

class ImageView;
class ButtonView;
class TextView;

class CreditsScreenUIController : public IUIController
{
private:
	// Constants:
	const sf::String game_title = "Outscal Presents - Snake Game";

	const float text_top_offset = 260.f;
	const int font_size = 120;

	const float button_width = 400.f;
	const float button_height = 140.f;

	const float menu_button_y_position = 600.f;
	const float quit_button_y_position = 800.f;

	const float background_alpha = 85.f;

	const sf::Color text_color = sf::Color(0, 200, 0);

	ImageView* background_image;
	TextView* title_text;

	ButtonView* menu_button;
	ButtonView* quit_button;

	void createText();
	void createImage();
	void createButtons();

	void initializeText();
	void initializeBackgroundImage();
	void initializeButtons();

	void registerButtonCallback();
	float calculateLeftOffsetForButton();

	float calculateTextWidth(sf::String text_value);

	void menuButtonCallback();
	void quitButtonCallback();

	void destroy();

public:
	CreditsScreenUIController();
	~CreditsScreenUIController();

	void initialize() override;
	void update() override;
	void render() override;
	void show() override;
};