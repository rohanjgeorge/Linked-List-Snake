#include "../header/GameService.h"
#include "../header/GraphicService.h"
#include "../header/ServiceLocator.h"

GameState GameService::current_state = GameState::BOOT;

GameService::GameService()
{
	service_locator = nullptr;
}

GameService::~GameService()
{
	destroy();
}

void GameService::ignite()
{
	service_locator = ServiceLocator::getInstance();
	initialize();
}

void GameService::initialize()
{
	service_locator->initialize();
	initializeVariables();
}

void GameService::initializeVariables()
{
	game_window = service_locator->getGraphicService()->getGameWindow();
}

bool GameService::isRunning() { return service_locator->getGraphicService()->isGameWindowOpen(); }

void GameService::setGameState(GameState new_state)
{
	current_state = new_state;
}

GameState GameService::getGameState()
{
	return current_state;
}

// Main Game Loop.
void GameService::update()
{
	// Update Game Logic.
	service_locator->update();
}

void GameService::render()
{
	game_window->clear();
	service_locator->render();
	game_window->display();
}

void GameService::destroy()
{
	service_locator->deleteServiceLocator();
}