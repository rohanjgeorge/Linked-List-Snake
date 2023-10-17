#pragma once
#include <SFML/System/Vector2.hpp>
#include "Node.h"
#include <vector>

class SingleLinkedList;
enum class Direction;
enum class FoodType;

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
	const float restart_duration = 4.f;

	const sf::Vector2i default_position = sf::Vector2i(25, 13);
	const Direction default_direction = Direction::RIGHT;

	PlayerState current_player_state;
	float elapsed_duration;
	float restart_counter;
	Direction current_player_direction;

	int player_score;
	TimeComplexity time_complexity;

	SingleLinkedList* single_linked_list;

	void createLinkedList();
	void handlePlayerInput();
	void handleLinkedListUpdate();
	void handlePlayerCollision();
	void handleNodeCollision();
	void handleElementsCollision();
	void handleFoodCollision();
	void performOperation(FoodType food_type);
	void handleRestart();
	void reset();
	void destroy();

public:
	PlayerController();
	~PlayerController();

	void initialize();
	void update();
	void render();

	void spawnPlayer();
	void respawnPlayer();
	void setPlayerState(PlayerState state);
	PlayerState getPlayerState();

	std::vector<sf::Vector2i> getCurrentPlayerPositionList();
	int getPlayerScore();
	TimeComplexity getTimeComplexity();
};