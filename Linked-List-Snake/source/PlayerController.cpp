#include "../header/PlayerController.h"
#include "../header/SingleLinkedList.h"
#include "../header/ServiceLocator.h"
#include "../header/LevelService.h"
#include "../header/TimeService.h"
#include "../header/EventService.h"
#include "../header/ElementService.h"
#include "../header/FoodService.h"
#include "../header/SoundService.h"
#include "../header/Food.h"

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
	switch (player_state)
	{
	case PlayerState::ALIVE:
		handleButtonInteraction();
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

void PlayerController::handlePlayerCollision()
{
	handleNodeCollision();
	handleElementsCollision();
	handleFoodCollision();
}

void PlayerController::handleNodeCollision()
{
	if (single_linked_list->handleNodeCollision())
	{
		player_state = PlayerState::DEAD;
		ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::DEATH);
	}
}

void PlayerController::handleElementsCollision()
{
	ElementService* element_service = ServiceLocator::getInstance()->getElementService();

	if(element_service->handleElementsCollision(single_linked_list->getHeadNodeReference()))
	{
		player_state = PlayerState::DEAD;
		ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::DEATH);
	}
}

void PlayerController::handleFoodCollision()
{
	FoodService* food_service = ServiceLocator::getInstance()->getFoodService();
	FoodType food_type;

	if (food_service->handleFoodCollision(single_linked_list->getHeadNodeReference(), food_type))
	{
		ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::PICKUP);

		food_service->destroyFood();
		performOperation(food_type);

		player_score++;
	}
}

void PlayerController::performOperation(FoodType food_type)
{
	switch (food_type)
	{
	case FoodType::PIZZA:
		single_linked_list->insertNodeAtHead();
		time_complexity = TimeComplexity::ONE;
		break;

	case FoodType::BURGER:
		single_linked_list->insertNodeAtTail();
		time_complexity = TimeComplexity::N;
		break;

	case FoodType::CHEESE:
		single_linked_list->insertNodeAt(2);
		time_complexity = TimeComplexity::N;
		break;

	case FoodType::APPLE:
		single_linked_list->removeNodeAtHead();
		time_complexity = TimeComplexity::ONE;
		break;

	case FoodType::MANGO:
		single_linked_list->removeNodeAtTail();
		time_complexity = TimeComplexity::N;
		break;

	case FoodType::ORANGE:
		single_linked_list->removeNodeAt(3);
		time_complexity = TimeComplexity::N;
		break;

	case FoodType::POISION:
		single_linked_list->removeHalfNodes();
		break;

	case FoodType::ALCOHOL:	
		player_direction = single_linked_list->reverse();
		break;
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
	player_state = PlayerState::ALIVE;
	player_direction = default_direction;
	elapsed_duration = 0.f;
	restart_counter = 0.f;
	player_score = 0;
	time_complexity = TimeComplexity::ONE;
}

void PlayerController::respawnPlayer()
{
	single_linked_list->removeAllNodes();
	reset();
	spawnPlayer();
}

void PlayerController::setPlayerSet(PlayerState state)
{
	player_state = state;
}

PlayerState PlayerController::getPlayerState()
{
	return player_state;
}

std::vector<sf::Vector2i> PlayerController::getCurrentPlayerPositionList()
{
	return single_linked_list->getNodesPositionList();
}

int PlayerController::getPlayerScore()
{
	return single_linked_list->getLinkedListSize();
}

TimeComplexity PlayerController::getTimeComplexity()
{
	return time_complexity;
}

void PlayerController::destroy()
{
	delete (single_linked_list);
}