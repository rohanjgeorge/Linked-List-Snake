#pragma once
#include <SFML/System/Vector2.hpp>
#include "Node.h"

class SingleLinkedList;
enum class Direction;

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
	const Direction default_direction = Direction::RIGHT;

	PlayerState player_state;
	float elapsed_duration;
	float restart_counter;
	Direction player_direction;

	SingleLinkedList* single_linked_list;

	void createLinkedList();
	void handleButtonInteraction();
	void handleLinkedListUpdate();
	void handlePlayerCollision();
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
	void setPlayerSet(PlayerState state);
	PlayerState getPlayerState();
};