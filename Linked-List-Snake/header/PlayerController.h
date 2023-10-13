#pragma once
#include <SFML/System/Vector2.hpp>
#include "Node.h"

class SingleLinkedList;
enum class Direction;

class PlayerController
{
private:
	const int initial_snake_length = 10;
	const float movement_frame_duration = 0.1f;

	const sf::Vector2i default_position = sf::Vector2i(25, 13);
	const Direction default_direction = Direction::RIGHT;

	float elapsed_duration;
	Direction player_direction;

	SingleLinkedList* single_linked_list;

	void createLinkedList();
	void handleButtonInteraction();
	void handleLinkedListUpdate();
	void destroy();

public:
	PlayerController();
	~PlayerController();

	void initialize();
	void update();
	void render();

	void spawnPlayer();
};