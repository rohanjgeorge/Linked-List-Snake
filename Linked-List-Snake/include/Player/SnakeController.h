#pragma once
#include <SFML/System/Vector2.hpp>
#include "LinkedListLib/Node.h"
#include "LinkedListLib/LinkedList.h"
#include "Food/FoodType.h"
#include "Level/LevelConfig.h"

namespace Player
{
	enum class TimeComplexity
	{
		ONE,
		N,
	};

	enum class SnakeState
	{
		ALIVE,
		DEAD,
	};

	class SnakeController
	{
	private:
		const int initial_snake_length = 10;
		const float movement_frame_duration = 0.1f;
		const float restart_duration = 2.f;

		const sf::Vector2i default_position = sf::Vector2i(25, 13);
		const LinkedListLib::Direction default_direction = LinkedListLib::Direction::RIGHT;

		SnakeState current_snake_state;
		float elapsed_duration;
		float restart_counter;
		LinkedList::Direction current_snake_direction;

		int player_score;
		TimeComplexity time_complexity;

		LinkedListLib::LinkedList* linked_list;

		void initializeLinkedList();

		void createLinkedList();
		void processPlayerInput();

		void moveSnake();
		void processSnakeCollision();
		
		void processBodyCollision();
		void processElementsCollision();
		void processFoodCollision();

		void OnFoodCollected(Food::FoodType food_type);
		int getRandomBodyPartIndex();

		void handleRestart();
		void reset();
		void destroy();

	public:
		SnakeController();
		~SnakeController();

		void initialize();
		void update();
		void render();

		void createLinkedList(Level::LevelType level_type);
		void spawnSnake();
		void respawnSnake();
		void setSnakeState(SnakeState state);
		SnakeState getSnakeState();

		std::vector<sf::Vector2i> getCurrentSnakePositionList();
		TimeComplexity getTimeComplexity();
		int getPlayerScore();
		bool isPlayerDead();
		int getSnakeSize();
	};
}