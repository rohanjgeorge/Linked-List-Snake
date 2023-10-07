#include "InstructionUIController.h"

InstructionUIController::InstructionUIController(sf::RenderWindow* window)
{
	this->game_window = window;
}

void InstructionUIController::show()
{

}

void InstructionUIController::update()
{
	game_window->clear(instructions_bg_color);
}