#pragma once
#include "LinkedList/BodyPart.h"

namespace LinkedList
{
	struct Node
	{
		BodyPart data;
		Node* next_node = nullptr;
	};
}