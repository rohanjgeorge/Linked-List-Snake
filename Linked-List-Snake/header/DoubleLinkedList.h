#pragma once
#include "../header/LinkedList.h"

class DoubleLinkedList : public LinkedList
{
protected:
	virtual Node* createNode() override;

public:
	DoubleLinkedList();
	~DoubleLinkedList();

	void initializeNode(Node* new_node, Node* reference_node, Operation operation);

	void insertNodeAtTail() override;
	void insertNodeAtHead() override;
	void insertNodeAt(int index) override;
	void insertNodeAtIndex(int index, Node* new_node);

	void shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node);

	void removeNodeAtTail() override;
	void removeNodeAtHead() override;
	void removeNodeAt(int index) override;
	void removeNodeAtIndex(int index);
	void removeAllNodes() override;
	void removeHalfNodes() override;

	void shiftNodesAfterRemoval(Node* cur_node);

	Node* findNodeBeforeIndex(int index);
	Direction reverse() override;
	void reverseNodeDirections();
};