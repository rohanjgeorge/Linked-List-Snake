#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameplayUIController.h"
#include "InstructionUIController.h"
#include "MainMenuUIController.h"
#include "SplashScreenUIController.h"

enum class UIState
{
	SPLASH_SCREEN,
	MAIN_MENU,
	INSTRUCTIONS,
	GAMEPLAY
};

class UIService
{
private:
	sf::RenderWindow* game_Window;
	SplashScreenUIController* splash_screen_controller;
	MainMenuUIController* main_menu_controller;
	InstructionUIController* instructions_controller;
	GameplayUIController* gameplay_controller;
	UIState current_state;

	void initializeControllers();
	void showSplashScreen();
	void showMainMenu();
	void showInstructions();
	void showgameplay();

public:
	UIService();
	~UIService();

	void setWindow(sf::RenderWindow* window_to_set);
	void setUIState(UIState new_state);
	void updateUI();
};
