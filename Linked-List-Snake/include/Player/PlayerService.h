#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Player/PlayerController.h"

namespace Player
{
	class SnakeController;

	class PlayerService
	{
	private:
		SnakeController* snake_controller;

		void createController();
		void destroy();

	public:
		PlayerService();
		~PlayerService();

		void initialize();
		void update();
		void render();

		void spawnPlayer();

		int getPlayerSize();
		int getPlayerScore();
		TimeComplexity getTimeComplexity();
		PlayerState getPlayerState();
		std::vector<sf::Vector2i> getCurrentSnakePositionList();
	};
}