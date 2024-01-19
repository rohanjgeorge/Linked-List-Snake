#include "LinkedListLib/DoubleLinked/DoubleLinkedList.h"
#include "LinkedListLib/DoubleLinked/DoubleNode.h"
#include "Level/LevelView.h"
#include "Global/Config.h"

namespace LinkedListLib
{
    namespace DoubleLinked
    {
        Node* DoubleLinkedList::createNode()
        {
            return new DoubleNode();
        }

        DoubleLinkedList::DoubleLinkedList() = default;

        DoubleLinkedList::~DoubleLinkedList() = default;

        void DoubleLinkedList::insertNodeAtTail()
        {
            linked_list_size++;
            Node* new_node = createNode();
            Node* cur_node = head_node;

            if (cur_node == nullptr)
            {
                head_node = new_node;
                static_cast<DoubleNode*>(new_node)->setPreviousNodeReference(nullptr);
                initializeNode(new_node, nullptr, Operation::TAIL);
                return;
            }

            while (cur_node->getNextNode() != nullptr)
            {
                cur_node = cur_node->getNextNode();
            }

            cur_node->setNextNodeReference(new_node);
            static_cast<DoubleNode*>(new_node)->setPreviousNodeReference(cur_node);
            initializeNode(new_node, cur_node, Operation::TAIL);
        }

        void DoubleLinkedList::insertNodeAtHead()
        {
            linked_list_size++;
            Node* new_node = createNode();

            if (head_node == nullptr)
            {
                head_node = new_node;
                static_cast<DoubleNode*>(new_node)->setPreviousNodeReference(nullptr);
                initializeNode(new_node, nullptr, Operation::HEAD);
                return;
            }

            initializeNode(new_node, head_node, Operation::HEAD);

            new_node->setNextNodeReference(head_node);
            static_cast<DoubleNode*>(head_node)->setPreviousNodeReference(new_node);

            head_node = new_node;
        }

        void DoubleLinkedList::insertNodeAt(int index)
        {
            if (index < 0 || index >= linked_list_size) return;
            linked_list_size++;

            if (index == 0)
            {
                insertNodeAtHead();
                return;
            }

            Node* new_node = createNode();
            insertNodeAtIndex(index, new_node);
        }

        void DoubleLinkedList::insertNodeAtIndex(int index, Node* new_node)
        {
            int current_index = 0;
            Node* cur_node = head_node;
            Node* prev_node = nullptr;

            initializeNode(new_node, head_node, Operation::TAIL);

            while (cur_node != nullptr && current_index < index)
            {
                prev_node = cur_node;
                cur_node = cur_node->getNextNode();
                current_index++;
            }

            prev_node->setNextNodeReference(new_node);
            static_cast<DoubleNode*>(new_node)->setPreviousNodeReference(prev_node);
            new_node->setNextNodeReference(cur_node);
            static_cast<DoubleNode*>(cur_node)->setPreviousNodeReference(new_node);

            shiftNodesAfterInsertion(new_node, cur_node, prev_node);
        }

        void DoubleLinkedList::shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node)
        {
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

            initializeNode(cur_node, prev_node, Operation::TAIL);
        }

        void DoubleLinkedList::removeNodeAtTail()
        {
            if (head_node == nullptr) return;
            linked_list_size--;

            Node* cur_node = head_node;

            if (cur_node->getNextNode() == nullptr)
            {
                removeNodeAtHead();
                return;
            }

            while (cur_node->getNextNode() != nullptr)
            {
                cur_node = cur_node->getNextNode();
            }

            Node* previous_node = static_cast<DoubleNode*>(cur_node)->getPreviousNode();
            previous_node->setNextNodeReference(nullptr);
            delete (cur_node);
        }

        void DoubleLinkedList::removeNodeAtHead()
        {
            Node* cur_node = head_node;
            head_node = head_node->getNextNode();

            if (head_node != nullptr)
            {
                static_cast<DoubleNode*>(head_node)->setPreviousNodeReference(nullptr);
            }

            cur_node->setNextNodeReference(nullptr);
            delete (cur_node);
        }

        void DoubleLinkedList::removeNodeAt(int index)
        {
            if (index < 0 || index >= linked_list_size) return;
            linked_list_size--;

            if (index == 0)
            {
                removeNodeAtHead();
            }
            else
            {
                removeNodeAtIndex(index);
            }
        }

        void DoubleLinkedList::removeNodeAtIndex(int index)
        {
            int current_index = 0;
            Node* cur_node = head_node;
            Node* prev_node = nullptr;

            while (cur_node != nullptr && current_index < index)
            {
                prev_node = cur_node;
                cur_node = cur_node->getNextNode();
                current_index++;
            }

            if (prev_node != nullptr)
            {
                prev_node->setNextNodeReference(cur_node->getNextNode());
            }

            if (cur_node->getNextNode() != nullptr)
            {
                Node* next_node = cur_node->getNextNode();
                static_cast<DoubleNode*>(next_node)->setPreviousNodeReference(prev_node);
            }

            shiftNodesAfterRemoval(cur_node);
            delete(cur_node);
        }

        void DoubleLinkedList::shiftNodesAfterRemoval(Node* cur_node)
        {
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
        }

        void DoubleLinkedList::removeAllNodes()
        {
            if (head_node == nullptr) return;
            linked_list_size = 0;

            while (head_node != nullptr)
            {
                removeNodeAtHead();
            }
        }

        void DoubleLinkedList::removeHalfNodes()
        {
            if (linked_list_size <= 1) return;
            int half_length = linked_list_size / 2;

            Node* prev_node = findNodeBeforeIndex(linked_list_size - half_length);
            Node* cur_node = prev_node->getNextNode();

            while (cur_node != nullptr)
            {
                Node* node_to_delete = cur_node;
                cur_node = cur_node->getNextNode();

                delete (node_to_delete);
                linked_list_size--;
            }

            prev_node->setNextNodeReference(nullptr);
        }

        Node* DoubleLinkedList::findNodeBeforeIndex(int index)
        {
            int current_index = 0;
            Node* cur_node = head_node;
            Node* prev_node = nullptr;

            while (cur_node != nullptr && current_index < index)
            {
                prev_node = cur_node;
                cur_node = cur_node->getNextNode();
                current_index++;
            }

            return prev_node;
        }

        Direction DoubleLinkedList::reverse()
        {
            Node* cur_node = head_node;
            Node* prev_node = nullptr;
            Node* next_node = nullptr;

            while (cur_node != nullptr)
            {
                next_node = cur_node->getNextNode();
                cur_node->setNextNodeReference(prev_node);
                static_cast<DoubleNode*>(cur_node)->setPreviousNodeReference(next_node);

                prev_node = cur_node;
                cur_node = next_node;
            }

            head_node = prev_node;

            reverseNodeDirections();
            return head_node->getDirection();
        }

        void DoubleLinkedList::reverseNodeDirections()
        {
            Node* cur_node = head_node;
            Node* next_node = cur_node->getNextNode();

            while (cur_node != nullptr && next_node != nullptr)
            {
                cur_node->setNodeDirection(next_node->getReverseNodeDirection());

                cur_node = next_node;
                next_node = cur_node->getNextNode();
            }
        }

        void DoubleLinkedList::initializeNode(Node* new_node, Node* reference_node, Operation operation)
        {
            if (reference_node == nullptr)
            {
                new_node->initialize(node_width, node_height, default_position, default_direction);
                return;
            }

            sf::Vector2i position = getNewNodePosition(reference_node, operation);

            new_node->initialize(node_width, node_height, position, reference_node->getDirection());
        }
    }
}