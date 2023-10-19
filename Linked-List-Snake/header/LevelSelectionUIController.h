#pragma once
#include <SFML/Graphics.hpp>
#include "../header/IUIController.h"

class ButtonView;
class ImageView;

class LevelSelectionUIController : public IUIController
{
private:
	// Constants:
	const float button_width = 400.f;
	const float button_height = 140.f;

	const float level_one_button_y_position = 400.f;
	const float level_two_button_y_position = 600.f;
	const float menu_button_y_position = 800.f;

	const float background_alpha = 85.f;

	ImageView* background_image;

	ButtonView* level_one_button;
	ButtonView* level_two_button;
	ButtonView* menu_button;

	void createImage();
	void createButtons();
	void initializeBackgroundImage();
	void initializeButtons();
	void registerButtonCallback();
	float calculateLeftOffsetForButton();

	void levelOneButtonCallback();
	void levelTwoButtonCallback();
	void menuButtonCallback();

	void destroy();

public:
	LevelSelectionUIController();
	~LevelSelectionUIController();

	void initialize() override;
	void update() override;
	void render() override;
	void show() override;
};