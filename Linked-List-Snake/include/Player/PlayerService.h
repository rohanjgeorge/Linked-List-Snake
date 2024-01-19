#pragma once

namespace Player
{
	class SnakeController;

	class PlayerService
	{
	private:
		SnakeController* player_controller;

		void createController();
		void destroy();

	public:
		PlayerService();
		~PlayerService();

		void initialize();
		void update();
		void render();

		void spawnPlayer();
	};
}