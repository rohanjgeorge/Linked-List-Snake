#include "Player/PlayerController.h"
#include "Global/ServiceLocator.h"
#include "Level/LevelService.h"
#include "Event/EventService.h"
#include "Element/ElementService.h"
#include "Food/FoodService.h"
#include "Main/GameService.h"

namespace Player
{
	using namespace LinkedList;
	using namespace Global;
	using namespace Level;
	using namespace Event;
	using namespace Time;
	using namespace Element;
	using namespace Sound;
	using namespace Main;
	using namespace Food;

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

		single_linked_list->initialize(width, height, default_position, default_direction);
		reset();
	}

	void PlayerController::update()
	{
		switch (current_player_state)
		{
		case PlayerState::ALIVE:
			handlePlayerInput();
			processPlayerCollision();
			handleLinkedListUpdate();
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

	void PlayerController::handleLinkedListUpdate()
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
		processNodeCollision();
		processElementsCollision();
		processFoodCollision();
	}

	void PlayerController::processNodeCollision()
	{
		if (single_linked_list->processNodeCollision())
		{
			current_player_state = PlayerState::DEAD;
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::DEATH);
		}
	}

	void PlayerController::processElementsCollision()
	{
		ElementService* element_service = ServiceLocator::getInstance()->getElementService();

		if (element_service->processElementsCollision(single_linked_list->getHeadNode()))
		{
			current_player_state = PlayerState::DEAD;
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::DEATH);
		}
	}

	void PlayerController::processFoodCollision()
	{
		FoodService* food_service = ServiceLocator::getInstance()->getFoodService();
		FoodType food_type;

		if (food_service->processFoodCollision(single_linked_list->getHeadNode(), food_type))
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
			single_linked_list->insertNodeAt(getRandomNodeIndex());
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
			single_linked_list->removeNodeAt(getRandomNodeIndex());
			time_complexity = TimeComplexity::N;
			break;

		case FoodType::POISION:
			single_linked_list->removeHalfNodes();
			time_complexity = TimeComplexity::N;
			break;

		case FoodType::ALCOHOL:
			current_player_direction = single_linked_list->reverse();
			time_complexity = TimeComplexity::N;
			break;
		}
	}

	void PlayerController::handleRestart()
	{
		restart_counter += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

		if (restart_counter >= restart_duration)
		{
			reset();
			GameService::setGameState(GameState::CREDITS);
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
		single_linked_list->removeAllNodes();

		current_player_state = PlayerState::ALIVE;
		time_complexity = TimeComplexity::ONE;

		current_player_direction = default_direction;
		elapsed_duration = 0.f;
		restart_counter = 0.f;
		player_score = 0;
	}

	void PlayerController::respawnPlayer()
	{
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

	int PlayerController::getPlayerScore()
	{
		return player_score;
	}

	TimeComplexity PlayerController::getTimeComplexity()
	{
		return time_complexity;
	}

	int PlayerController::getPlayreSize()
	{
		return single_linked_list->getLinkedListSize();
	}

	int PlayerController::getRandomNodeIndex()
	{
		return std::rand() % (single_linked_list->getLinkedListSize() - 1);
	}

	void PlayerController::destroy()
	{
		delete (single_linked_list);
	}
}