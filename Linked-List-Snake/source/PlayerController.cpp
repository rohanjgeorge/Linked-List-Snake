#include "../header/PlayerController.h"
#include "../header/SingleLinkedList.h"
#include "../header/ServiceLocator.h"
#include "../header/LevelService.h"
#include "../header/LevelController.h"
#include "../header/LevelModel.h"
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
	float width = ServiceLocator::getInstance()->getLevelService()->getLevelController()->getLevelModel()->getGridCellWidth();
	float height = ServiceLocator::getInstance()->getLevelService()->getLevelController()->getLevelModel()->getGridCellHeight();

	single_linked_list->initialize(width, height, default_position, default_direction);
	player_direction = default_direction;
	elapsed_duration = 0.f;
}

void PlayerController::update()
{
	handleButtonInteraction();
	handleLinkedListUpdate();
}

void PlayerController::render()
{
	single_linked_list->render();
}

void PlayerController::handleButtonInteraction()
{
	EventService* event_service = ServiceLocator::getInstance()->getEventService();

	if (event_service->pressedUpKey() && player_direction != Direction::DOWN)
	{
		player_direction = Direction::UP;
	}
	else if (event_service->pressedDownKey() && player_direction != Direction::UP)
	{
		player_direction = Direction::DOWN;
	}
	else if (event_service->pressedLeftKey() && player_direction != Direction::RIGHT)
	{
		player_direction = Direction::LEFT;
	}
	else if (event_service->pressedRightKey() && player_direction != Direction::LEFT)
	{
		player_direction = Direction::RIGHT;
	}
}

void PlayerController::handleLinkedListUpdate()
{
	elapsed_duration += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

	if (elapsed_duration >= movement_frame_duration)
	{
		single_linked_list->update(player_direction);
		elapsed_duration = 0.f;
	}
}

void PlayerController::spawnPlayer()
{
	for (int i = 0; i < initial_snake_length; i++)
	{
		single_linked_list->insertNode();
	}
}

void PlayerController::destroy()
{
	delete (single_linked_list);
}