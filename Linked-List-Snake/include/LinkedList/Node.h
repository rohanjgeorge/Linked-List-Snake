#pragma once
#include "LinkedList/BodyPart.h"

namespace LinkedList
{
	struct Node
	{
		BodyPart body_part;
		Node* next_node = nullptr;
	};
}