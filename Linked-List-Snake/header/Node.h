#pragma once
#include <SFML/System/Vector2.hpp>

class ImageView;

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class Node
{
private:
	Node* next_node;

	ImageView* node_image;

	sf::Vector2i grid_position;
	Direction direction;

	float node_width;
	float node_height;

	void initializeNodeUI();
	sf::Vector2f getNodeScreenPosition();

	sf::Vector2i getNextPositionUp();
	sf::Vector2i getNextPositionDown();
	sf::Vector2i getNextPositionLeft();
	sf::Vector2i getNextPositionRight();

public:
	Node();
	~Node();

	void initialize(float width, float height, sf::Vector2i pos, Direction dir);
	void updateNode(Direction dir);
	void render();

	void setNextNodeReference(Node* node);
	Node* getNextNode();
	Direction getDirection();
	sf::Vector2i getPosition();
	sf::Vector2i getNextNodePosition();
};