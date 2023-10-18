#pragma once
#include <SFML/Graphics.hpp>

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
protected:
	Node* next_node;

	ImageView* node_image;

	sf::Vector2i grid_position;
	Direction node_direction;

	float node_width;
	float node_height;

	void createNodeUI();
	void initializeNodeUI();
	sf::Vector2f getNodeScreenPosition();
	float getRotationAngle();

	sf::Vector2i getNextPositionUp();
	sf::Vector2i getNextPositionDown();
	sf::Vector2i getNextPositionLeft();
	sf::Vector2i getNextPositionRight();

	void destroy();

public:
	Node();
	virtual ~Node();

	void initialize(float width, float height, sf::Vector2i pos, Direction dir);
	void updateNode(Direction dir);
	void render();

	void setNextNodeReference(Node* node);
	Node* getNextNode();

	Direction getDirection();
	sf::Vector2i getPosition();
	sf::Vector2i getNextNodePosition();
	sf::Vector2i getPrevNodePosition();
	Direction getReverseNodeDirection();

	void setNodePosition(sf::Vector2i position);
	void setNodeDirection(Direction direction);
};