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

class SingleLinkedList
{
private:
	Node* head_node;

	float node_width;
	float node_height;

	sf::Vector2i default_position;
	Direction default_direction;

	int linked_list_size;

	Node* createNode();
	void initializeNode(Node* new_node, Node* reference_node, Operation operation);
	sf::Vector2i getNewNodePosition(Node* reference_node, Operation operation);

	void updateNodes(Direction directionToSet);

public:
	SingleLinkedList();
	~SingleLinkedList();

	void initialize(float width, float height, sf::Vector2i position, Direction direction);
	void update(Direction direction);
	void render();

	void insertNodeAtTail();
	void insertNodeAtHead();
	void insertNodeAt(int index);
	void insertNodeAtIndex(int index, Node* new_node);

	void shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node);

	void removeNodeAtTail();
	void removeNodeAtHead();
	void removeNodeAt(int index);
	void removeNodeAtIndex(int index);
	void removeAllNodes();
	void removeHalfNodes();

	void shiftNodesAfterRemoval(Node* cur_node);

	Node* findNodeBeforeIndex(int index);
	Direction reverse();
	void reverseNodeDirections();

	bool handleNodeCollision();
	Node* getHeadNode();
	int getLinkedListSize();

	std::vector<sf::Vector2i> getNodesPositionList();
};