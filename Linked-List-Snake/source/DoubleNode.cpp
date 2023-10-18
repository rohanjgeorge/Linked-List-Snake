#include "../header/DoubleNode.h"

DoubleNode::DoubleNode() = default;

DoubleNode::~DoubleNode() = default;

Node* DoubleNode::getPreviousNode()
{
	return previous_node;
}

void DoubleNode::setPreviousNodeReference(Node* node)
{
	previous_node = node;
}
