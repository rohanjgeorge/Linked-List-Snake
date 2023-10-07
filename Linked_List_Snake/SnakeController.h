#pragma once
#include "SFML/Graphics/Sprite.hpp"

class SnakeController
{
private:
	const int initial_size = 4;

public:
	SnakeController();
	~SnakeController();
	void turnLeft();
	void turnRight();
	void increaseSize(/* FoodType foodType */);
	void decreaseSize(/* FoodType foodType */);
	void reverseDirection();
};

class SnakeBody
{
public:
	sf::Sprite sprite;
	int position;

};

