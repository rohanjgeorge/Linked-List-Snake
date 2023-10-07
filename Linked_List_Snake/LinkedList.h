#pragma once

namespace LinkedList
{
    template <typename T>
    class NodeBase {
    public:
        T data;

        NodeBase(T& value) : data(value) {}
    };

    template <typename T, typename Node>
    class LinkedListBase {
    protected:
        Node* head;

    public:
        LinkedListBase() : head(nullptr) {}
        virtual ~LinkedListBase();

        virtual void insertAtHead(T& value) = 0;
        virtual void insertAtTail(T& value) = 0;
        virtual void insertAt(T& value, int position) = 0;
        virtual void deleteAtHead(T& value) = 0;
        virtual void deleteAtTail(T& value) = 0;
        virtual void deleteAt(T& value, int position) = 0;
        virtual void reverse() = 0;
        virtual void split() = 0;
    };
}
