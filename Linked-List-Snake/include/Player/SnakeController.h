#pragma once
#include <SFML/System/Vector2.hpp>
#include "LinkedListLib/Node.h"
#include "LinkedListLib/LinkedList.h"
#include "Food/FoodType.h"
#include "Level/LevelConfig.h"

namespace Player
{
	using namespace Level;
	using namespace Food;
	using namespace LinkedListLib;

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

	enum class InputState
	{
		WAITING,
		PROCESSING
	};

	class SnakeController
	{
	private:
		const int initial_snake_length = 4;
		const float movement_frame_duration = 0.1f;
		const float restart_duration = 2.f;

		const int minimum_snake_size = 3;

		const sf::Vector2i default_position = sf::Vector2i(25, 13);
		const Direction default_direction = Direction::RIGHT;

		SnakeState current_snake_state;
		float elapsed_duration;
		float restart_counter;
		Direction current_snake_direction;
		InputState current_input_state;

		int player_score;
		TimeComplexity time_complexity;

		LinkedList* linked_list;

		void initializeLinkedList();

		void createLinkedList();
		void processPlayerInput();
		void delayedUpdate();
		void moveSnake();
		void processSnakeCollision();
		
		void processBodyCollision();
		void processElementsCollision();
		void processFoodCollision();

		void OnFoodCollected(FoodType food_type);
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

		void createLinkedList(LinkedListType level_type);
		void spawnSnake();
		void respawnSnake();
		void setSnakeState(SnakeState state);
		SnakeState getSnakeState();

		std::vector<sf::Vector2i> getCurrentSnakePositionList();
		TimeComplexity getTimeComplexity();
		int getPlayerScore();
		bool isSnakeDead();
		int getSnakeSize();
		bool isSnakeSizeMinimum();
	};
}