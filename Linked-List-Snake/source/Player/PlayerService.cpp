#include "Player/PlayerService.h"
#include "Player/PlayerController.h"

namespace Player
{
	using namespace Level;

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

	void PlayerService::spawnPlayer(LevelType level_type)
	{
		player_controller->createLinkedList(level_type);
		player_controller->spawnPlayer();
	}

	std::vector<sf::Vector2i> PlayerService::getCurrentPlayerPositionList()
	{
		return player_controller->getCurrentPlayerPositionList();
	}

	int PlayerService::getPlayerSize()
	{
		return player_controller->getPlayreSize();
	}

	int PlayerService::getPlayerScore()
	{
		return player_controller->getPlayerScore();
	}

	TimeComplexity PlayerService::getTimeComplexity()
	{
		return player_controller->getTimeComplexity();
	}

	PlayerState PlayerService::getPlayerState()
	{
		return player_controller->getPlayerState();
	}

	bool PlayerService::isPlayerDead()
	{
		return player_controller->isPlayerDead();
	}

	void PlayerService::destroy()
	{
		delete (player_controller);
	}
}