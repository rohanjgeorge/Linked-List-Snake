#include "GameplayUIController.h"

GameplayUIController::GameplayUIController(sf::RenderWindow* window)
{
	this->game_window = window;
}

void GameplayUIController::show()
{

}

void GameplayUIController::update()
{
	game_window->clear(gameplay_bg_color);
}
