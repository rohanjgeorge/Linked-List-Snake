#pragma once
#include "../header/IUIController.h"

class TextView;

class GameplayUIController : public IUIController
{
private:
	// Constants:
	const float font_size = 60.f;

	const float text_y_position = 7.f;
	const float level_number_text_x_position = 65.f;
	const float score_text_x_position = 800.f;
	const float time_complexity_text_x_position = 1320.f;

	TextView* level_number_text;
	TextView* score_text;
	TextView* time_complexity_text;

	void createTexts();
	void initializeTexts();
	void initializeLevelNumberText();
	void initializeScoreText();
	void initializeTimeComplexityText();

	void destroy();

public:
	GameplayUIController();
	~GameplayUIController();

	void initialize() override;
	void update() override;
	void render() override;
	void show() override;
};