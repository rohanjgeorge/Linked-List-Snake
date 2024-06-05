#include "LinkedList/SingleLinkedList.h"
#include "Player/BodyPart.h"
#include "Level/LevelView.h"
#include <iostream>

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
			cur_node->body_part.render();
			cur_node = cur_node->next_node;
		}
	}

	void SingleLinkedList::updateNodes(Direction directionToSet)
	{
		Node* cur_node = head_node;
		Direction node_direction = directionToSet;

		while (cur_node != nullptr)
		{
			Direction previous_direction = cur_node->body_part.getDirection();

			cur_node->body_part.update(node_direction);

			node_direction = previous_direction;
			cur_node = cur_node->next_node;
		}
	}

	bool SingleLinkedList::processNodeCollision()
	{
		if (head_node == nullptr) return false;

		sf::Vector2i predicted_position = head_node->body_part.getNextPosition();

		Node* cur_node = head_node->next_node;
		while (cur_node != nullptr)
		{
			// if (cur_node->body_part.getNextPosition() == predicted_position || cur_node->body_part.getPosition() == head_node->body_part.getPosition()) return true;
			
			if (cur_node->body_part.getNextPosition() == predicted_position)
			{
				return true;
			}

			/*if (cur_node->body_part.getPosition() == head_node->body_part.getPosition())
			{
				std::cout << "current node position = " << cur_node->body_part.getPosition().x << "," << cur_node->body_part.getPosition().y 
							<< "\tcurrent head position = " << head_node->body_part.getPosition().x << "," << head_node->body_part.getPosition().y
							<< "\n";
				return true;
			}*/

			cur_node = cur_node->next_node;
		}

		return false;
	}

	void SingleLinkedList::insertNodeAtTail()
	{
		Node* new_node = createNode();
		Node* cur_node = head_node;

		if (cur_node == nullptr) //If there is no head, then create a new head node
		{
			head_node = new_node;
			new_node->body_part.initialize(node_width, node_height, default_position, default_direction);
			return;
		}

		while (cur_node->next_node != nullptr)
		{
			cur_node = cur_node->next_node;
		}

		cur_node->next_node = new_node;
		new_node->body_part.initialize(node_width, node_height, getNewNodePosition(cur_node), cur_node->body_part.getDirection());
	}

	void SingleLinkedList::removeNodeAtHead()
	{
		Node* cur_node = head_node;
		head_node = head_node->next_node;

		cur_node->next_node = nullptr;
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
		Direction reference_direction = reference_node->body_part.getDirection();
		sf::Vector2i reference_position = reference_node->body_part.getPosition();

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