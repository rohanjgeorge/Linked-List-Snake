#pragma once

class SingleLinkedList;

class PlayerController
{
private:
	const int initial_snake_length = 5;

	SingleLinkedList* single_linked_list;

	void createLinkedList();
	void destroy();

public:
	PlayerController();
	~PlayerController();

	void initialize();
	void update();
	void render();

	void spawnPlayer();
};