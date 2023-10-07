#include "GameEngine.h"

GameEngine::GameEngine() { initializeVariables(); }

GameEngine::~GameEngine() { service_locator->deleteServiceLocator(); }

void GameEngine::initializeVariables() { service_locator = ServiceLocator::getInstance(); }

void GameEngine::ignite()
{
	initializeGameWindow();
	service_locator->getUIService()->setUIState(UIState::SPLASH_SCREEN);
}

void GameEngine::initializeGameWindow()
{
	// Game Window will be created here.
	service_locator->getGraphicService()->createGameWindow();
	service_locator->getGraphicService()->setFrameRate(frame_rate);

	// Pass down the reference of the game window through service locator.
	service_locator->setGameWindow();
}

bool GameEngine::isRunning() { return service_locator->getGraphicService()->isGameWindowOpen(); }

// Main Game Loop.
void GameEngine::update()
{
	// Process Events.
	service_locator->getEventService()->processEvents();

	// Update Game Logic.
	service_locator->updateServices();

	// Render Next Frame.
	service_locator->getGraphicService()->drawNextFrame();
}
