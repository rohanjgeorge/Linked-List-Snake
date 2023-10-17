#include "../header/PlayerController.h"
#include "../header/SingleLinkedList.h"
#include "../header/ServiceLocator.h"
#include "../header/LevelService.h"
#include "../header/TimeService.h"
#include "../header/EventService.h"

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
		handlePlayerInput();
		handleLinkedListUpdate();
		handlePlayerCollision();
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

void PlayerController::handlePlayerInput()
{
	EventService* event_service = ServiceLocator::getInstance()->getEventService();

	if (event_service->pressedUpKey() && current_player_direction != Direction::DOWN)
	{
		current_player_direction = Direction::UP;
	}
	else if (event_service->pressedDownKey() && current_player_direction != Direction::UP)
	{
		current_player_direction = Direction::DOWN;
	}
	else if (event_service->pressedLeftKey() && current_player_direction != Direction::RIGHT)
	{
		current_player_direction = Direction::LEFT;
	}
	else if (event_service->pressedRightKey() && current_player_direction != Direction::LEFT)
	{
		current_player_direction = Direction::RIGHT;
	}
}

void PlayerController::handleLinkedListUpdate()
{
	elapsed_duration += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

	if (elapsed_duration >= movement_frame_duration)
	{
		single_linked_list->update(current_player_direction);
		elapsed_duration = 0.f;
	}
}

void PlayerController::handlePlayerCollision()
{
	if (single_linked_list->handleNodeCollision())
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

void PlayerController::destroy()
{
	delete (single_linked_list);
}