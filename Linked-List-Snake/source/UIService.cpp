#include "../header/UIService.h"
#include "../header/GameService.h"
#include "../header/MainMenuUIController.h"
#include "../header/SplashScreenUIController.h"
#include "../header/LevelSelectionUIController.h"
#include "../header/GameplayUIController.h"
#include "../header/TextView.h"
#include "../header/CreditsScreenUIController.h"

UIService::UIService()
{
	splash_screen_controller = nullptr;
	main_menu_controller = nullptr;
	level_selection_ui_controller = nullptr;
	gameplay_ui_controller = nullptr;
	credits_screen_ui_controller = nullptr;

	createControllers();
}

void UIService::createControllers()
{
	splash_screen_controller = new SplashScreenUIController();
	main_menu_controller = new MainMenuUIController();
	level_selection_ui_controller = new LevelSelectionUIController();
	gameplay_ui_controller = new GameplayUIController();
	credits_screen_ui_controller = new CreditsScreenUIController();
}

UIService::~UIService()
{
	destroy();
}

void UIService::initialize()
{
	TextView::initializeTextView();
	initializeControllers();
}

void UIService::update()
{
	IUIController* ui_controller = getCurrentUIController();

	if (ui_controller)
	{
		ui_controller->update();
	}
}

void UIService::render()
{
	IUIController* ui_controller = getCurrentUIController();

	if (ui_controller)
	{
		ui_controller->render();
	}
}

void UIService::showScreen()
{
	IUIController* ui_controller = getCurrentUIController();

	if (ui_controller)
	{
		ui_controller->show();
	}
}

void UIService::initializeControllers()
{
	splash_screen_controller->initialize();
	main_menu_controller->initialize();
	level_selection_ui_controller->initialize();
	gameplay_ui_controller->initialize();
	credits_screen_ui_controller->initialize();
}

IUIController* UIService::getCurrentUIController()
{
	switch (GameService::getGameState())
	{
	case GameState::SPLASH_SCREEN:
		return splash_screen_controller;

	case GameState::MAIN_MENU:
		return main_menu_controller;

	case GameState::LEVEL_SELECTION:
		return level_selection_ui_controller;

	case GameState::GAMEPLAY:
		return gameplay_ui_controller;

	case GameState::CREDITS:
		return credits_screen_ui_controller;

	default:
		return nullptr;
	}
}

void UIService::destroy()
{
	delete(splash_screen_controller);
	delete(main_menu_controller);
	delete(level_selection_ui_controller);
	delete(gameplay_ui_controller);
	delete(credits_screen_ui_controller);
}