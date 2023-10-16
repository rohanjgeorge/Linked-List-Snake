#include "../header/SingleLinkedList.h"
#include "../header/LevelView.h"

SingleLinkedList::SingleLinkedList()
{
	head_node = nullptr;
}

SingleLinkedList::~SingleLinkedList() = default;

void SingleLinkedList::initialize(float width, float height, sf::Vector2i position, Direction direction)
{
	node_width = width;
	node_height = height;
	default_position = position;
	default_direction = direction;
}

void SingleLinkedList::update(Direction direction)
{
	updateNodes(direction);
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

void SingleLinkedList::updateNodes(Direction direction)
{
	Node* cur_node = head_node;
	Direction node_direction = direction;

	while (cur_node != nullptr)
	{
		Direction temp_direction = cur_node->getNodeDirection();

		cur_node->updateNode(node_direction);

		node_direction = temp_direction;
		cur_node = cur_node->getNextNodeReference();
	}
}

bool SingleLinkedList::handleNodeCollision()
{
	if (head_node == nullptr) return false;

	sf::Vector2i predicted_position = head_node->getNextNodePosition();

	Node* cur_node = head_node->getNextNodeReference();
	while (cur_node != nullptr)
	{
		if (cur_node->getNodePosition() == predicted_position) return true;
		cur_node = cur_node->getNextNodeReference();
	}

	return false;
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
		cur_node = cur_node->getNextNodeReference();
	}
	
	delete (cur_node->getNextNodeReference());
	cur_node->setNextNodeReference(nullptr);
}

void SingleLinkedList::removeAllNodes()
{
	if (head_node == nullptr) return;

	Node* cur_node = head_node;

	if (cur_node->getNextNodeReference() == nullptr)
	{
		delete(head_node);
		head_node = nullptr;
	}

	while (cur_node->getNextNodeReference()->getNextNodeReference() != nullptr)
	{
		Node* temp_node = cur_node;
		cur_node = cur_node->getNextNodeReference();

		temp_node->setNextNodeReference(nullptr);
		delete(temp_node);
	}

	delete(cur_node);
	head_node = nullptr;
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

std::vector<sf::Vector2i> SingleLinkedList::getNodesPositionList()
{
	std::vector<sf::Vector2i> nodes_position_list;

	Node* cur_node = head_node;

	while (cur_node != nullptr)
	{
		nodes_position_list.push_back(cur_node->getNodePosition());
		cur_node = cur_node->getNextNodeReference();
	}

	return nodes_position_list;
}
