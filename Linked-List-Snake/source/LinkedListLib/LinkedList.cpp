#include "LinkedListLib/LinkedList.h"
#include "Level/LevelView.h"
#include "Global/Config.h"

namespace LinkedListLib
{
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
            cur_node->body_part.render();
            cur_node = cur_node->next_node;
        }
    }

    void LinkedList::updateNodes(Direction directionToSet)
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

    bool LinkedList::processNodeCollision()
    {
        if (head_node == nullptr) return false;

        sf::Vector2i predicted_position = head_node->body_part.getNextPosition();

        Node* cur_node = head_node->next_node;
        while (cur_node != nullptr)
        {
            if (cur_node->body_part.getPosition() == predicted_position || cur_node->body_part.getPosition() == head_node->body_part.getPosition()) return true;
            cur_node = cur_node->next_node;
        }

        return false;
    }

    Node* LinkedList::createNode()
    {
        return new Node();
    }

    sf::Vector2i LinkedList::getNewNodePosition(Node* reference_node, Operation operation)
    {
        switch (operation)
        {
        case Operation::HEAD:
            return reference_node->body_part.getNextPosition();
        case Operation::TAIL:
            return reference_node->body_part.getPrevPosition();
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
            nodes_position_list.push_back(cur_node->body_part.getPosition());
            cur_node = cur_node->next_node;
        }

        return nodes_position_list;
    }

    int LinkedList::findMiddleNode()
    {
        Node* slow = head_node;
        Node* fast = head_node;
        int midIndex = 0;  // This will track the index of the middle node.

        // Move fast pointer at 2x speed and slow pointer at 1x speed.
        while (fast != nullptr && fast->next_node != nullptr) {
            slow = slow->next_node;
            fast = fast->next_node->next_node;
            midIndex++;
        }

        // Now, slow is at the middle node
        return midIndex;
    }
}