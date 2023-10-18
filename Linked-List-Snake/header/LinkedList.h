#pragma once
#include <SFML/System/Vector2.hpp>
#include "../header/Node.h"
#include <vector>

class Node;
enum class Direction;

enum class Operation
{
	HEAD,
	MID,
	TAIL,
};

class LinkedList
{
protected:
	Node* head_node;

	float node_width;
	float node_height;

	sf::Vector2i default_position;
	Direction default_direction;

	int linked_list_size;

	virtual Node* createNode() = 0;
	sf::Vector2i getNewNodePosition(Node* reference_node, Operation operation);

	void updateNodes(Direction directionToSet);

public:
	LinkedList();
	virtual ~LinkedList();

	void initialize(float width, float height, sf::Vector2i position, Direction direction);
	void update(Direction direction);
	void render();

	virtual void insertNodeAtTail() = 0;
	virtual void insertNodeAtHead() = 0;
	virtual void insertNodeAt(int index) = 0;

	virtual void removeNodeAtTail() = 0;
	virtual void removeNodeAtHead() = 0;
	virtual void removeNodeAt(int index) = 0;
	virtual void removeAllNodes() = 0;
	virtual void removeHalfNodes() = 0;

	virtual Direction reverse() = 0;

	bool handleNodeCollision();
	Node* getHeadNode();
	int getLinkedListSize();

	std::vector<sf::Vector2i> getNodesPositionList();
};