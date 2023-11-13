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

	enum class PlayerState
	{
		ALIVE,
		DEAD,
	};

	class PlayerController
	{
	private:
		const int initial_snake_length = 10;
		const float movement_frame_duration = 0.1f;
		const float restart_duration = 2.f;

		const sf::Vector2i default_position = sf::Vector2i(25, 13);
		const LinkedListLib::Direction default_direction = LinkedListLib::Direction::RIGHT;

		PlayerState current_player_state;
		float elapsed_duration;
		float restart_counter;
		LinkedListLib::Direction current_player_direction;

		int player_score;
		TimeComplexity time_complexity;

		LinkedListLib::LinkedList* linked_list;

		void initializeLinkedList();

		void processPlayerInput();
		void processLinkedListUpdate();
		void processPlayerCollision();
		void processNodeCollision();
		void processElementsCollision();
		void processFoodCollision();

		void performOperation(Food::FoodType food_type);
		int getRandomNodeIndex();

		void handleRestart();
		void reset();
		void destroy();

	public:
		PlayerController();
		~PlayerController();

		void initialize();
		void update();
		void render();

		void createLinkedList(Level::LevelType level_type);
		void spawnPlayer();
		void respawnPlayer();
		void setPlayerState(PlayerState state);
		PlayerState getPlayerState();

		std::vector<sf::Vector2i> getCurrentPlayerPositionList();
		TimeComplexity getTimeComplexity();
		int getPlayerScore();
		int getPlayreSize();

		bool isPlayerDead();
	};
}