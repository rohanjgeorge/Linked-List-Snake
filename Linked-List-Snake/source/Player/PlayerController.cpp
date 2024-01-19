#include "Player/PlayerController.h"
#include "Global/ServiceLocator.h"
#include "Level/LevelService.h"
#include "Event/EventService.h"
#include "Element/ElementService.h"
#include "Food/FoodService.h"
#include "Main/GameService.h"
#include "LinkedListLib/SingleLinked/SingleLinkedList.h"
#include "LinkedListLib/DoubleLinked/DoubleLinkedList.h"

namespace Player
{
	using namespace LinkedListLib;
	using namespace SingleLinked;
	using namespace DoubleLinked;
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
		linked_list = nullptr;
	}

	PlayerController::~PlayerController()
	{
		destroy();
	}

	void PlayerController::createLinkedList(LevelType level_type)
	{
		switch (level_type)
		{
		case LevelType::SINGLE_LINKED_LIST:
			linked_list = new SingleLinkedList();
			break;
		case LevelType::DOUBLE_LINKED_LIST:
			linked_list = new DoubleLinkedList();
			break;
		}

		initializeLinkedList();
	}

	void PlayerController::initializeLinkedList()
	{
		float width = ServiceLocator::getInstance()->getLevelService()->getCellWidth();
		float height = ServiceLocator::getInstance()->getLevelService()->getCellHeight();

		linked_list->initialize(width, height, default_position, default_direction);
		reset();
	}

	void PlayerController::initialize() { }

	void PlayerController::update()
	{
		switch (current_player_state)
		{
		case PlayerState::ALIVE:
			processPlayerInput();
			processPlayerCollision();
			processLinkedListUpdate();
			break;

		case PlayerState::DEAD:
			handleRestart();
			break;
		}
	}

	void PlayerController::render()
	{
		linked_list->render();
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
			linked_list->update(current_player_direction);
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
		if (linked_list->processNodeCollision())
		{
			current_player_state = PlayerState::DEAD;
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::DEATH);
		}
	}

	void PlayerController::processElementsCollision()
	{
		ElementService* element_service = ServiceLocator::getInstance()->getElementService();

		if (element_service->processElementsCollision(linked_list->getHeadNode()))
		{
			current_player_state = PlayerState::DEAD;
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::DEATH);
		}
	}

	void PlayerController::processFoodCollision()
	{
		FoodService* food_service = ServiceLocator::getInstance()->getFoodService();
		FoodType food_type;

		if (food_service->processFoodCollision(linked_list->getHeadNode(), food_type))
		{
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::PICKUP);

			food_service->destroyFood();
			performLinkedListOperation(food_type);

			player_score++;
		}
	}

	void PlayerController::performLinkedListOperation(FoodType food_type)
	{
		switch (food_type)
		{
		case FoodType::PIZZA:
			linked_list->insertNodeAtHead();
			time_complexity = TimeComplexity::ONE;
			break;

		case FoodType::BURGER:
			linked_list->insertNodeAtTail();
			time_complexity = TimeComplexity::N;
			break;

		case FoodType::CHEESE:
			linked_list->insertNodeAt(getRandomNodeIndex());
			time_complexity = TimeComplexity::N;
			break;

		case FoodType::APPLE:
			linked_list->removeNodeAtHead();
			time_complexity = TimeComplexity::ONE;
			break;

		case FoodType::MANGO:
			linked_list->removeNodeAtTail();
			time_complexity = TimeComplexity::N;
			break;

		case FoodType::ORANGE:
			linked_list->removeNodeAt(getRandomNodeIndex());
			time_complexity = TimeComplexity::N;
			break;

		case FoodType::POISION:
			linked_list->removeHalfNodes();
			time_complexity = TimeComplexity::N;
			break;

		case FoodType::ALCOHOL:
			current_player_direction = linked_list->reverse();
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
			linked_list->insertNodeAtTail();
		}
	}

	void PlayerController::reset()
	{
		linked_list->removeAllNodes();

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
		return linked_list->getNodesPositionList();
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
		return linked_list->getLinkedListSize();
	}

	bool PlayerController::isPlayerDead()
	{
		return current_player_state == PlayerState::DEAD;
	}

	int PlayerController::getRandomNodeIndex()
	{
		return std::rand() % (linked_list->getLinkedListSize() - 1);
	}

	void PlayerController::destroy()
	{
		delete (linked_list);
	}
}