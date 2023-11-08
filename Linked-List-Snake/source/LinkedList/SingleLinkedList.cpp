#include "LinkedList/SingleLinkedList.h"
#include "Level/LevelView.h"

namespace LinkedList
{
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
			cur_node = cur_node->getNextNode();
		}
	}

	void SingleLinkedList::updateNodes(Direction directionToSet)
	{
		Node* cur_node = head_node;
		Direction node_direction = directionToSet;

		while (cur_node != nullptr)
		{
			Direction previous_direction = cur_node->getDirection();

			cur_node->updateNode(node_direction);

			node_direction = previous_direction;
			cur_node = cur_node->getNextNode();
		}
	}

	bool SingleLinkedList::handleNodeCollision()
	{
		if (head_node == nullptr) return false;

		sf::Vector2i predicted_position = head_node->getNextNodePosition();

		Node* cur_node = head_node->getNextNode();
		while (cur_node != nullptr)
		{
			if (cur_node->getPosition() == predicted_position) return true;
			cur_node = cur_node->getNextNode();
		}

		return false;
	}

	void SingleLinkedList::insertNodeAtTail()
	{
		Node* new_node = createNode();
		Node* cur_node = head_node;

		if (cur_node == nullptr)
		{
			head_node = new_node;
			new_node->initialize(node_width, node_height, default_position, default_direction);
			return;
		}

		while (cur_node->getNextNode() != nullptr)
		{
			cur_node = cur_node->getNextNode();
		}

		cur_node->setNextNodeReference(new_node);
		new_node->initialize(node_width, node_height, getNewNodePosition(cur_node), cur_node->getDirection());
	}

	void SingleLinkedList::removeNodeAtHead()
	{
		Node* cur_node = head_node;
		head_node = head_node->getNextNode();

		cur_node->setNextNodeReference(nullptr);
		delete (cur_node);
	}

	void SingleLinkedList::removeAllNodes()
	{
		if (head_node == nullptr) return;

		while (head_node != nullptr)
		{
			removeNodeAtHead();
		}
	}

	Node* SingleLinkedList::createNode()
	{
		return new Node();
	}

	sf::Vector2i SingleLinkedList::getNewNodePosition(Node* reference_node)
	{
		Direction reference_direction = reference_node->getDirection();
		sf::Vector2i reference_position = reference_node->getPosition();

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

	Node* SingleLinkedList::getHeadNode()
	{
		return head_node;
	}
}