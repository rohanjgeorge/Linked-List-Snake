#include "../header/PlayerService.h"
#include "../header/PlayerController.h"

PlayerService::PlayerService()
{
	player_controller = nullptr;

	createController();
}

PlayerService::~PlayerService()
{
	destroy();
}

void PlayerService::createController()
{
	player_controller = new PlayerController();
}

void PlayerService::initialize()
{
	player_controller->initialize();
}

void PlayerService::update()
{
	player_controller->update();
}

void PlayerService::render()
{
	player_controller->render();
}

void PlayerService::spawnPlayer()
{
	player_controller->spawnPlayer();
}

void PlayerService::destroy()
{
	delete (player_controller);
}