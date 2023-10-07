#include "../header/UIService.h"
#include "../header/GameService.h"
#include "../header/GraphicService.h"
#include "../header/SplashScreenUIController.h"

UIService::UIService()
{
	splash_screen_controller = nullptr;
	game_window = nullptr;

	createControllers();
}

void UIService::createControllers()
{
	splash_screen_controller = new SplashScreenUIController();
}

UIService::~UIService()
{
	destroy();
}

void UIService::initialize()
{
	game_window = ServiceLocator::getInstance()->getGameWindow();
	initializeControllers();
}

void UIService::update()
{
	switch (GameService::getGameState())
	{
	case GameState::SPLASH_SCREEN:
		splash_screen_controller->update();
		break;
	}
}

void UIService::render()
{
	switch (GameService::getGameState())
	{
	case GameState::SPLASH_SCREEN:
		splash_screen_controller->render();
		break;
	}
}

void UIService::show()
{
	switch (GameService::getGameState())
	{
	case GameState::SPLASH_SCREEN:
		splash_screen_controller->show();
		break;
	}
}

void UIService::initializeControllers()
{
	splash_screen_controller->initialize();
}

void UIService::destroy()
{
	delete(splash_screen_controller);
}