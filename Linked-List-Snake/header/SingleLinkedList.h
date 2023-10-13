#pragma once
#include <SFML/System/Vector2.hpp>
#include "../header/Node.h"

class Node;
enum class Direction;

class SingleLinkedList
{
private:
	const sf::Vector2i default_position = sf::Vector2i(25, 13);
	const Direction default_direction = Direction::RIGHT;

	Node* head_node;

	float node_width;
	float node_height;

	Node* createNode();
	void initializeNode(Node* new_node, Node* reference_node);
	sf::Vector2i getNewNodePosition(Node* reference_node);

public:
	SingleLinkedList();
	~SingleLinkedList();

	void initialize(float width, float height);
	void update();
	void render();

	void insertNode();
	void removeNode();

	Node* getHeadNodeReference();
};