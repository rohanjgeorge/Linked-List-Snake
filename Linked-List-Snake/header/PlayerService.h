#pragma once

class PlayerController;

class PlayerService
{
private:
	PlayerController* player_controller;

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