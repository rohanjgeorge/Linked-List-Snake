#pragma once
#include "../header/Node.h"

class DoubleNode : public Node
{
private:
	Node* previous_node;

public:
	DoubleNode();
	~DoubleNode();

	void setPreviousNodeReference(Node* node);
	Node* getPreviousNode();
};