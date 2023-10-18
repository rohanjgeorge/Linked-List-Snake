#include "../header/SingleLinkedList.h"
#include "../header/LevelView.h"
#include "../header/Config.h"

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
	linked_list_size = 0;
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
	linked_list_size++;

	Node* new_node = createNode();
	Node* cur_node = head_node;

	if (cur_node == nullptr)
	{
		head_node = new_node;
		initializeNode(new_node, nullptr, Operation::TAIL);
		return;
	}

	while (cur_node->getNextNode() != nullptr)
	{
		cur_node = cur_node->getNextNode();
	}
	
	cur_node->setNextNodeReference(new_node);
	initializeNode(new_node, cur_node, Operation::TAIL);
}

void SingleLinkedList::insertNodeAtHead()
{
	linked_list_size++;

	Node* new_node = createNode();

	if (head_node == nullptr)
	{
		head_node = new_node;
		initializeNode(new_node, nullptr, Operation::HEAD);
		return;
	}

	initializeNode(new_node, head_node, Operation::HEAD);
	new_node->setNextNodeReference(head_node);
	head_node = new_node;
}

void SingleLinkedList::insertNodeAt(int index)
{
	if (index < 0 || index > linked_list_size) return;

	linked_list_size++;
	int current_index = 0;

	if (index == 0)
	{
		insertNodeAtHead();
		return;
	}

	Node* cur_node = head_node;
	Node* prev_node = nullptr;
	Node* new_node = createNode();
	initializeNode(new_node, head_node, Operation::TAIL);

	// Find the node at the index before the insertion point.
	while (cur_node != nullptr && current_index < index) 
	{
		prev_node = cur_node;
		cur_node = cur_node->getNextNode();
		current_index++;
	}

	// Insert the new node between prev_node and cur_node.
	prev_node->setNextNodeReference(new_node);
	new_node->setNextNodeReference(cur_node);

	// Shift positions and directions of nodes from the inserted node onward.
	Node* next_node = cur_node;
	cur_node = new_node;

	while (cur_node != nullptr && next_node != nullptr) 
	{
		cur_node->setNodePosition(next_node->getPosition());
		cur_node->setNodeDirection(next_node->getDirection());

		prev_node = cur_node;
		cur_node = next_node;
		next_node = next_node->getNextNode();
	}

	// Initialize the last node in the shifted section.
	initializeNode(cur_node, prev_node, Operation::TAIL);
}

void SingleLinkedList::removeNodeAtTail()
{
	if (head_node == nullptr) return;

	linked_list_size--;

	Node* cur_node = head_node;

	if (cur_node->getNextNode() == nullptr)
	{
		delete(head_node);
		head_node = nullptr;
		return;
	}

	while (cur_node->getNextNode()->getNextNode() != nullptr )
	{
		cur_node = cur_node->getNextNode();
	}
	
	delete (cur_node->getNextNode());
	cur_node->setNextNodeReference(nullptr);
}

void SingleLinkedList::removeNodeAtHead()
{
	if (head_node == nullptr) return;

	linked_list_size--;

	Node* cur_node = head_node;
	head_node = head_node->getNextNode();

	cur_node->setNextNodeReference(nullptr);
	delete (cur_node);
}

void SingleLinkedList::removeNodeAt(int index)
{
	if (index < 0 || index >= linked_list_size) return;

	linked_list_size--;

	Node* cur_node = head_node;
	Node* prev_node = nullptr;

	int current_index = 0;

	if (index == 0)
	{
		removeNodeAtHead();
		return;
	}

	// Find the node at the index to be removed.
	while (cur_node != nullptr && current_index < index) 
	{
		prev_node = cur_node;
		cur_node = cur_node->getNextNode();
		current_index++;
	}

	// Remove the node by updating the references.
	prev_node->setNextNodeReference(cur_node->getNextNode());

	Node* temp_node = cur_node;

	sf::Vector2i previous_node_position = cur_node->getPosition();
	Direction previous_node_direction = cur_node->getDirection();

	cur_node = cur_node->getNextNode();

	while (cur_node != nullptr)
	{
		sf::Vector2i temp_node_position = cur_node->getPosition();
		Direction temp_node_direction = cur_node->getDirection();

		cur_node->setNodePosition(previous_node_position);
		cur_node->setNodeDirection(previous_node_direction);

		cur_node = cur_node->getNextNode();
		previous_node_position = temp_node_position;
		previous_node_direction = temp_node_direction;
	}

	temp_node->setNextNodeReference(nullptr);
	delete(temp_node);
}

void SingleLinkedList::removeAllNodes()
{
	if (head_node == nullptr) return;

	linked_list_size = 0;

	Node* cur_node = head_node;

	if (cur_node->getNextNode() == nullptr)
	{
		delete(head_node);
		head_node = nullptr;
	}

	while (cur_node->getNextNode()->getNextNode() != nullptr)
	{
		Node* temp_node = cur_node;
		cur_node = cur_node->getNextNode();

		temp_node->setNextNodeReference(nullptr);
		delete(temp_node);
	}

	delete(cur_node);
	head_node = nullptr;
}

void SingleLinkedList::removeHalfNodes()
{
	if (linked_list_size <= 1) return;

	int half_length = linked_list_size / 2;

	Node* cur_node = head_node;
	Node* prev_node = nullptr;

	// Traverse to the node where you want to start removing from the back.
	for (int i = 0; i < linked_list_size - half_length; i++) 
	{
		prev_node = cur_node;
		cur_node = cur_node->getNextNode();
	}

	while (cur_node != nullptr) 
	{
		Node* node_to_delete = cur_node;
		cur_node = cur_node->getNextNode();

		delete node_to_delete;
		linked_list_size--;
	}

	prev_node->setNextNodeReference(nullptr);
}

Direction SingleLinkedList::reverse()
{
	Node* cur_node = head_node;
	Node* prev_node = nullptr;
	Node* next_node = nullptr;

	while (cur_node != nullptr)
	{
		next_node = cur_node->getNextNode();
		cur_node->setNextNodeReference(prev_node);

		prev_node = cur_node;
		cur_node = next_node;
	}

	head_node = prev_node;

	reverseNodeDirections();
	return head_node->getDirection();
}

void SingleLinkedList::reverseNodeDirections()
{
	if (head_node->getNextNode() == nullptr)
	{
		head_node->setNodeDirection(head_node->getReverseNodeDirection());
		return;
	}

	Node* cur_node = head_node;
	Node* next_node = head_node->getNextNode();

	while (cur_node != nullptr && next_node != nullptr)
	{
		cur_node->setNodeDirection(next_node->getReverseNodeDirection());
		cur_node = next_node;
		next_node = next_node->getNextNode();
	}
}

Node* SingleLinkedList::createNode()
{
	return new Node();
}

void SingleLinkedList::initializeNode(Node* new_node, Node* reference_node, Operation operation)
{
	if (reference_node == nullptr)
	{
		new_node->initialize(node_width, node_height, default_position, default_direction);
		return;
	}

	sf::Vector2i position = getNewNodePosition(reference_node, operation);

	new_node->initialize(node_width, node_height, position, reference_node->getDirection());
}

sf::Vector2i SingleLinkedList::getNewNodePosition(Node* reference_node, Operation operation)
{
	Direction reference_direction = reference_node->getDirection();
	sf::Vector2i reference_position = reference_node->getPosition();

	switch (operation)
	{
	case Operation::HEAD:
		return reference_node->getNextNodePosition();
	case Operation::TAIL:
		return reference_node->getPrevNodePosition();
	}

	return default_position;
}

Node* SingleLinkedList::getHeadNode()
{
	return head_node;
}

int SingleLinkedList::getLinkedListSize()
{
	return linked_list_size;
}

std::vector<sf::Vector2i> SingleLinkedList::getNodesPositionList()
{
	std::vector<sf::Vector2i> nodes_position_list;

	Node* cur_node = head_node;

	while (cur_node != nullptr)
	{
		nodes_position_list.push_back(cur_node->getPosition());
		cur_node = cur_node->getNextNode();
	}

	return nodes_position_list;
}