#pragma once
#include <SFML/System/Vector2.hpp>
#include "../header/Node.h"
#include <vector>

class Node;
enum class Direction;

class SingleLinkedList
{
private:
	Node* head_node;

	float node_width;
	float node_height;

	sf::Vector2i default_position;
	Direction default_direction;

	Node* createNode();
	void initializeNode(Node* new_node, Node* reference_node);
	sf::Vector2i getNewNodePosition(Node* reference_node);

	void updateNodes(Direction direction);

public:
	SingleLinkedList();
	~SingleLinkedList();

	void initialize(float width, float height, sf::Vector2i position, Direction direction);
	void update(Direction direction);
	void render();

	void insertNode();
	void removeNode();
	void removeAllNodes();

	bool handleNodeCollision();
	Node* getHeadNodeReference();

	std::vector<sf::Vector2i> getNodesPositionList();
};