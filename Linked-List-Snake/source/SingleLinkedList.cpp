#include "../header/SingleLinkedList.h"
#include "../header/LevelView.h"

SingleLinkedList::SingleLinkedList()
{
}

SingleLinkedList::~SingleLinkedList()
{
}

void SingleLinkedList::initialize(float width, float height)
{
	node_width = width;
	node_height = height;
}

void SingleLinkedList::update()
{
}

void SingleLinkedList::render()
{
	Node* cur_node = head_node;

	while (cur_node != nullptr)
	{
		cur_node->render();
		cur_node = cur_node->getNextNodeReference();
	}
}

void SingleLinkedList::insertNode()
{
	Node* new_node = createNode();
	Node* cur_node = head_node;

	if (cur_node == nullptr)
	{
		head_node = new_node;
		initializeNode(new_node, nullptr);
		return;
	}

	while (cur_node->getNextNodeReference() != nullptr)
	{
		cur_node = cur_node->getNextNodeReference();
	}
	
	cur_node->setNextNodeReference(new_node);
	initializeNode(new_node, cur_node);
}

void SingleLinkedList::removeNode()
{
	if (head_node == nullptr) return;

	Node* cur_node = head_node;

	if (cur_node->getNextNodeReference() == nullptr)
	{
		delete(head_node);
		head_node = nullptr;
	}

	while (cur_node->getNextNodeReference()->getNextNodeReference() != nullptr )
	{
		delete (cur_node->getNextNodeReference());
		cur_node->setNextNodeReference(nullptr);
	}
}

Node* SingleLinkedList::createNode()
{
	return new Node();
}

void SingleLinkedList::initializeNode(Node* new_node, Node* reference_node)
{
	if (reference_node == nullptr)
	{
		new_node->initialize(node_width, node_height, default_position, default_direction);
		return;
	}

	sf::Vector2i position = getNewNodePosition(reference_node);

	new_node->initialize(node_width, node_height, position, reference_node->getNodeDirection());
}

sf::Vector2i SingleLinkedList::getNewNodePosition(Node* reference_node)
{
	Direction reference_direction = reference_node->getNodeDirection();
	sf::Vector2i reference_position = reference_node->getNodePosition();

	switch (reference_direction)
	{
	case Direction::UP:
		return sf::Vector2i(reference_position.x, reference_position.y - 1);
		break;
	case Direction::DOWN:
		return sf::Vector2i(reference_position.x, reference_position.y + 1);
		break;
	case Direction::LEFT:
		return sf::Vector2i(reference_position.x + 1, reference_position.y);
		break;
	case Direction::RIGHT:
		return sf::Vector2i(reference_position.x - 1, reference_position.y);
		break;
	}

	return default_position;
}

Node* SingleLinkedList::getHeadNodeReference()
{
	return head_node;
}
