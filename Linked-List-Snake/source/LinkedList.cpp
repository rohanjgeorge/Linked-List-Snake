#include "../header/LinkedList.h"
#include "../header/LevelView.h"
#include "../header/Config.h"

LinkedList::LinkedList()
{
    head_node = nullptr;
}

LinkedList::~LinkedList() = default;

void LinkedList::initialize(float width, float height, sf::Vector2i position, Direction direction)
{
    node_width = width;
    node_height = height;
    default_position = position;
    default_direction = direction;
    linked_list_size = 0;
}

void LinkedList::update(Direction direction)
{
    updateNodes(direction);
}

void LinkedList::render()
{
    Node* cur_node = head_node;

    while (cur_node != nullptr)
    {
        cur_node->render();
        cur_node = cur_node->getNextNode();
    }
}

void LinkedList::updateNodes(Direction directionToSet)
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

bool LinkedList::handleNodeCollision()
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

Node* LinkedList::createNode()
{
    return new Node();
}

sf::Vector2i LinkedList::getNewNodePosition(Node* reference_node, Operation operation)
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

Node* LinkedList::getHeadNode()
{
    return head_node;
}

int LinkedList::getLinkedListSize()
{
    return linked_list_size;
}

std::vector<sf::Vector2i> LinkedList::getNodesPositionList()
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