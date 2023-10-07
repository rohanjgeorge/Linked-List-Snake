#pragma once
#include "LinkedList.h"

namespace SinglyLinkedList
{
    template <typename T>
    class Node : public LinkedList::NodeBase<T>
	{
    public:
        Node(T& value) : LinkedList::NodeBase<T>(value), next(nullptr) {}
        Node<T>* next;
    };

    template <typename T>
    class List : public LinkedList::LinkedListBase<T, Node<T>>
    {
    public:
        void insertAtHead(T& value) override;
        void insertAtTail(T& value) override;
        void insertAt(T& value, int position) override;
        void deleteAtHead(T& value) override;
        void deleteAtTail(T& value) override;
        void deleteAt(T& value, int position) override;
        void reverse() override;
        void split() override;
    };
}
