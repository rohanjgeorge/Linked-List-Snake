#include "LinkedListLib/SingleLinked/SingleLinkedList.h"
#include "LinkedListLib/SingleLinked/SingleNode.h"
#include "Level/LevelView.h"

namespace LinkedListLib
{
    namespace SingleLinked
    {
        Node* SingleLinkedList::createNode()
        {
            return new SingleNode();
        }

        SingleLinkedList::SingleLinkedList() = default;

        SingleLinkedList::~SingleLinkedList() = default;

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

            while (cur_node->next_node != nullptr)
            {
                cur_node = cur_node->next_node;
            }

            cur_node->next_node = new_node;
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
            new_node->next_node = head_node;
            head_node = new_node;
        }

        void SingleLinkedList::insertNodeAt(int index)
        {
            if (index < 0 || index >= linked_list_size) return;

            if (index == 0)
            {
                insertNodeAtHead();
                return;
            }

            Node* new_node = createNode();
            insertNodeAtIndex(index, new_node);
        }

        void SingleLinkedList::insertNodeAtMiddle()
        {
            if (head_node == nullptr) {
                insertNodeAtHead();             // If the list is empty, insert at the head.
                return;
            }

            int midIndex = findMiddleNode();    // Use the existing function to find the middle index
            insertNodeAt(midIndex);             // Use the existing function to insert the node at the found index             
        }

        void SingleLinkedList::insertNodeAtIndex(int index, Node* new_node)
        {
            int current_index = 0;
            Node* cur_node = head_node;
            Node* prev_node = nullptr;

            initializeNode(new_node, head_node, Operation::TAIL);

            while (cur_node != nullptr && current_index < index)
            {
                prev_node = cur_node;
                cur_node = cur_node->next_node;
                current_index++;
            }

            linked_list_size++;
            prev_node->next_node = new_node;
            new_node->next_node = cur_node;

            shiftNodesAfterInsertion(new_node, cur_node, prev_node);
        }

        void SingleLinkedList::shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node)
        {
            Node* next_node = cur_node;
            cur_node = new_node;

            while (cur_node != nullptr && next_node != nullptr)
            {
                cur_node->body_part.setPosition(next_node->body_part.getPosition());
                cur_node->body_part.setDirection(next_node->body_part.getDirection());

                prev_node = cur_node;
                cur_node = next_node;
                next_node = next_node->next_node;
            }

            initializeNode(cur_node, prev_node, Operation::TAIL);
        }

        void SingleLinkedList::removeNodeAtTail()
        {
            if (head_node == nullptr) return;

            Node* cur_node = head_node;

            if (cur_node->next_node == nullptr)
            {
                removeNodeAtHead();
                return;
            }

            while (cur_node->next_node->next_node != nullptr)
            {
                cur_node = cur_node->next_node;
            }

            linked_list_size--;
            delete (cur_node->next_node);
            cur_node->next_node = nullptr;
        }

        void SingleLinkedList::removeNodeAtHead()
        {
            linked_list_size--;
            Node* cur_node = head_node;
            head_node = head_node->next_node;

            cur_node->next_node = nullptr;
            delete (cur_node);
        }

        void SingleLinkedList::removeNodeAtMiddle() {
            if (head_node == nullptr) return; // If the list is empty, there's nothing to remove

            int midIndex = findMiddleNode();  // Use the existing function to find the middle index
            removeNodeAt(midIndex);           // Use the existing function to remove the node at the found index
        }

        void SingleLinkedList::removeNodeAt(int index)
        {
            if (index < 0 || index >= linked_list_size) return;

            if (index == 0)
            {
                removeNodeAtHead();
            }
            else
            {
                removeNodeAtIndex(index);
            }
        }

        void SingleLinkedList::removeNodeAtIndex(int index)
        {
            linked_list_size--;
            int current_index = 0;
            Node* cur_node = head_node;
            Node* prev_node = nullptr;

            while (cur_node != nullptr && current_index < index)
            {
                prev_node = cur_node;
                cur_node = cur_node->next_node;
                current_index++;
            }

            prev_node->next_node = cur_node->next_node;

            shiftNodesAfterRemoval(cur_node);
            delete(cur_node);
        }

        void SingleLinkedList::shiftNodesAfterRemoval(Node* cur_node)
        {
            sf::Vector2i previous_node_position = cur_node->body_part.getPosition();
            Direction previous_node_direction = cur_node->body_part.getDirection();
            cur_node = cur_node->next_node;

            while (cur_node != nullptr)
            {
                sf::Vector2i temp_node_position = cur_node->body_part.getPosition();
                Direction temp_node_direction = cur_node->body_part.getDirection();

                cur_node->body_part.setPosition(previous_node_position);
                cur_node->body_part.setDirection(previous_node_direction);

                cur_node = cur_node->next_node;
                previous_node_position = temp_node_position;
                previous_node_direction = temp_node_direction;
            }
        }

        void SingleLinkedList::removeAllNodes()
        {
            if (head_node == nullptr) return;

            while (head_node != nullptr)
            {
                removeNodeAtHead();
            }
        }

        void SingleLinkedList::removeHalfNodes()
        {
            if (linked_list_size <= 1) return;
            int half_length = linked_list_size / 2;
            int new_tail_index = half_length - 1;

            Node* prev_node = findNodeAtIndex(new_tail_index);
            Node* cur_node = prev_node->next_node;

            while (cur_node != nullptr)
            {
                Node* node_to_delete = cur_node;
                cur_node = cur_node->next_node;

                delete (node_to_delete);
                linked_list_size--;
            }

            prev_node->next_node = nullptr;
        }

        Direction SingleLinkedList::reverse()
        {
            Node* cur_node = head_node;
            Node* prev_node = nullptr;
            Node* next_node = nullptr;

            while (cur_node != nullptr)
            {
                next_node = cur_node->next_node;
                cur_node->next_node = prev_node;

                prev_node = cur_node;
                cur_node = next_node;
            }

            head_node = prev_node;

            reverseNodeDirections();
            return head_node->body_part.getDirection();
        }

        void SingleLinkedList::reverseNodeDirections()
        {
            Node* cur_node = head_node;
            Node* next_node = cur_node->next_node;

            while (cur_node != nullptr && next_node != nullptr)
            {
                cur_node->body_part.setDirection(next_node->body_part.getReverseDirection());

                cur_node = next_node;
                next_node = cur_node->next_node;
            }
        }
    }
}