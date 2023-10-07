#include "UIService.h"

UIService::UIService() { game_Window = nullptr; }

void UIService::setWindow(sf::RenderWindow* window_to_set)
{
	game_Window = window_to_set;
	initializeControllers();
}

void UIService::initializeControllers()
{
	splash_screen_controller = new SplashScreenUIController(game_Window);
	main_menu_controller = new MainMenuUIController(game_Window);
	instructions_controller = new InstructionUIController(game_Window);
	gameplay_controller = new GameplayUIController(game_Window);
}

void UIService::updateUI()
{
	switch(current_state)
	{
	case UIState::SPLASH_SCREEN:
		break;
	case UIState::MAIN_MENU:
		main_menu_controller->update();
		break;
	case UIState::INSTRUCTIONS:
		instructions_controller->update();
		break;
	case UIState::GAMEPLAY:
		gameplay_controller->update();
		break;
	default: 
		break;
	}
}

void UIService::setUIState(UIState new_state)
{
	current_state = new_state;

	switch (current_state)
	{
	case UIState::SPLASH_SCREEN:
		showSplashScreen();
		break;
	case UIState::MAIN_MENU:
		showMainMenu();
		break;
	case UIState::INSTRUCTIONS:
		showInstructions();
		break;
	case UIState::GAMEPLAY:
		showgameplay();
		break;
	default:
		break;
	}
}

void UIService::showSplashScreen() { splash_screen_controller->show(); }

void UIService::showMainMenu() { main_menu_controller->show(); }

void UIService::showInstructions() { instructions_controller->show(); }

void UIService::showgameplay() { gameplay_controller->show(); }

UIService::~UIService()
{
	delete(splash_screen_controller);
	delete(main_menu_controller);
	delete(instructions_controller);
	delete(gameplay_controller);
}
