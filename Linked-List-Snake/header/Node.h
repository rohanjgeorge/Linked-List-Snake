#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

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

	sf::RenderWindow* game_window;

	sf::Texture node_texture;
	sf::Sprite node_sprite;

	sf::Vector2i position;
	Direction direction;

	float node_width;
	float node_height;

	void initializeNodeSprite();
	void scaleNodeSprite();
	void setNodeSpritePosition();
	sf::Vector2i getNextNodePosition();
	sf::Vector2i getNextPositionUp();
	sf::Vector2i getNextPositionDown();
	sf::Vector2i getNextPositionLeft();
	sf::Vector2i getNextPositionRight();

public:
	Node();
	~Node();

	void initialize(float width, float height, sf::Vector2i pos, Direction dir);
	void updateNodePosition(Direction dir);
	void render();

	void setNextNodeReference(Node* node);
	Node* getNextNodeReference();
	Direction getNodeDirection();
	sf::Vector2i getNodePosition();
};