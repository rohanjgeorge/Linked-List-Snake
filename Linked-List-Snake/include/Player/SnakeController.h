#pragma once
#include <SFML/System/Vector2.hpp>
#include "LinkedList/Node.h"
#include "LinkedList/SingleLinkedList.h"
#include "Food/FoodType.h"

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
		const LinkedList::Direction default_direction = LinkedList::Direction::RIGHT;

		SnakeState current_snake_state;
		float elapsed_duration;
		float restart_counter;
		LinkedList::Direction current_snake_direction;
		InputState current_input_state;

		int player_score;
		TimeComplexity time_complexity;

		LinkedList::SingleLinkedList* single_linked_list;

		void createLinkedList();
		void processPlayerInput();
		void delayedUpdate();
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

		void spawnSnake();
		void respawnSnake();
		void setSnakeState(SnakeState state);
		SnakeState getSnakeState();

		std::vector<sf::Vector2i> getCurrentSnakePositionList();
		TimeComplexity getTimeComplexity();
		int getPlayerScore();
		int getSnakeSize();
		bool isSnakeSizeMinimum();
	};
}