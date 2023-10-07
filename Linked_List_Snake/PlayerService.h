#pragma once
#include "SnakeController.h"

enum SnakeType
{
	Singly,
	Doubly
};

class PlayerService
{
private:
	SnakeController* snake;
	SnakeType type;

public:
	PlayerService();
	~PlayerService();
};
