#include "LinkedListLib/DoubleLinked/DoubleNode.h"

namespace LinkedListLib
{
	namespace DoubleLinked
	{
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
	}
}