#include "../header/GameService.h"

GameState GameService::current_state = GameState::BOOT;

GameService::GameService()
{
}

GameService::~GameService()
{
	destroy();
}

void GameService::ignite()
{
	initialize();
}

void GameService::initialize()
{
}

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
}

void GameService::render()
{
}

void GameService::destroy()
{
}