#pragma once
#include "LinkedListLib/Node.h"

namespace LinkedListLib
{
	namespace DoubleLinked
	{
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
	}
}