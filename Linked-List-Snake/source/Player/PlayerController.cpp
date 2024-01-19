#include "Player/PlayerController.h"
#include "Global/ServiceLocator.h"
#include "Level/LevelService.h"
#include "Event/EventService.h"

namespace Player
{
	using namespace LinkedList;
	using namespace Global;
	using namespace Level;
	using namespace Event;
	using namespace Time;

	PlayerController::PlayerController()
	{
		single_linked_list = nullptr;
		createLinkedList();
	}

	PlayerController::~PlayerController()
	{
		destroy();
	}

	void PlayerController::createLinkedList()
	{
		single_linked_list = new SingleLinkedList();
	}

	void PlayerController::initialize()
	{
		float width = ServiceLocator::getInstance()->getLevelService()->getCellWidth();
		float height = ServiceLocator::getInstance()->getLevelService()->getCellHeight();

		reset();
		single_linked_list->initialize(width, height, default_position, default_direction);
	}

	void PlayerController::update()
	{
		switch (current_player_state)
		{
		case PlayerState::ALIVE:
			processPlayerInput();
			processLinkedListUpdate();
			processPlayerCollision();
			break;

		case PlayerState::DEAD:
			handleRestart();
			break;
		}
	}

	void PlayerController::render()
	{
		single_linked_list->render();
	}

	void PlayerController::processPlayerInput()
	{
		EventService* event_service = ServiceLocator::getInstance()->getEventService();

		if (event_service->pressedUpArrowKey() && current_player_direction != Direction::DOWN)
		{
			current_player_direction = Direction::UP;
		}
		else if (event_service->pressedDownArrowKey() && current_player_direction != Direction::UP)
		{
			current_player_direction = Direction::DOWN;
		}
		else if (event_service->pressedLeftArrowKey() && current_player_direction != Direction::RIGHT)
		{
			current_player_direction = Direction::LEFT;
		}
		else if (event_service->pressedRightArrowKey() && current_player_direction != Direction::LEFT)
		{
			current_player_direction = Direction::RIGHT;
		}
	}

	void PlayerController::processLinkedListUpdate()
	{
		elapsed_duration += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

		if (elapsed_duration >= movement_frame_duration)
		{
			single_linked_list->update(current_player_direction);
			elapsed_duration = 0.f;
		}
	}

	void PlayerController::processPlayerCollision()
	{
		if (single_linked_list->processNodeCollision())
		{
			current_player_state = PlayerState::DEAD;
		}
	}

	void PlayerController::handleRestart()
	{
		restart_counter += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

		if (restart_counter >= restart_duration)
		{
			respawnPlayer();
		}
	}

	void PlayerController::spawnPlayer()
	{
		for (int i = 0; i < initial_snake_length; i++)
		{
			single_linked_list->insertNodeAtTail();
		}
	}

	void PlayerController::reset()
	{
		current_player_state = PlayerState::ALIVE;
		current_player_direction = default_direction;
		elapsed_duration = 0.f;
		restart_counter = 0.f;
	}

	void PlayerController::respawnPlayer()
	{
		single_linked_list->removeAllNodes();
		reset();
		spawnPlayer();
	}

	void PlayerController::setPlayerState(PlayerState state)
	{
		current_player_state = state;
	}

	PlayerState PlayerController::getPlayerState()
	{
		return current_player_state;
	}

	std::vector<sf::Vector2i> PlayerController::getCurrentPlayerPositionList()
	{
		return single_linked_list->getNodesPositionList();
	}

	void PlayerController::destroy()
	{
		delete (single_linked_list);
	}
}