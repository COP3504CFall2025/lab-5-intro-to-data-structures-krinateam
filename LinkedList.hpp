#pragma once
#include <iostream>
using namespace std;

//SOURCES USED
//https://www.geeksforgeeks.org/dsa/delete-a-node-in-a-doubly-linked-list/#deletion-at-the-beginning-in-doubly-linked-list
//^^ to help understand deletion of node

// https://www.geeksforgeeks.org/dsa/print-linked-list/
//^^ to help understand printing nodes

//adding node structure

template <typename T>
class LinkedList {
public:
    //node structure
    struct Node
    {
        T data;
        Node* prev;
        Node* next;
    };

	// Behaviors
	void printForward() const;
	void printReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const;
	Node* getHead();
	const Node* getHead() const;
	Node* getTail();
	const Node* getTail() const;

	// Insertion
	void addHead(const T& data);
	void addTail(const T& data);

	// Removal
	bool removeHead();
	bool removeTail();
	void Clear();

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};

template <typename T>
[[nodiscard]] unsigned int LinkedList<T>::getCount() const
{
    return count;
}

template <typename T>
LinkedList<T>::Node* LinkedList<T>::getHead()
{
    return head;
}

template <typename T>
const LinkedList<T>::Node* LinkedList<T>::getHead() const
{
    return head;
}

template <typename T>
LinkedList<T>::Node* LinkedList<T>::getTail()
{
    return tail;
}

template <typename T>
const LinkedList<T>::Node* LinkedList<T>::getTail() const
{
    return tail;
}

template <typename T>
void LinkedList<T>::addHead(const T& data)
{
    Node* newHead = new Node();
    newHead->data = data;
    newHead->prev = nullptr;

    Node* temp = head;
    newHead->next = temp;

    if(temp != nullptr)
    {
        temp->prev = newHead;
    }
    if(tail == nullptr)
    {
        tail = newHead;
    }
    head = newHead;
    count++;
}

template <typename T>
void LinkedList<T>::addTail(const T& data)
{
    Node* newTail = new Node();
    newTail->data = data;
    newTail->next = nullptr;

    Node* temp = tail;
    newTail->prev = temp;

    if(temp != nullptr)
    {
        temp->next = newTail;
    }
    if(head == nullptr)
    {
        head = newTail;
    }
    tail = newTail;
    count++;
}

template <typename T>
bool LinkedList<T>::removeHead()
{
    if(head == nullptr)
    {
        return false;
    }

    Node* temp = head;

    head = head->next;
    if(head != nullptr)
    {
        head->prev = nullptr;
    }

    delete temp;
    count--;
    return true;
}

template <typename T>
bool LinkedList<T>::removeTail()
{
    if(tail == nullptr)
    {
        return false;
    }

    Node* temp = tail;

    tail = tail->prev;
    if(tail != nullptr)
    {
        tail->next = nullptr;
    }

    delete temp;
    count--;
    return true;
}

template <typename T>
void LinkedList<T>::Clear()
{
    Node* track = head;

    while(track != nullptr)
    {
        track = head->next;
        delete head;
        head = track;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <typename T>
void LinkedList<T>::printForward() const
{
    Node* temp = head;
    while(temp != nullptr)
    {
        cout << temp->data;
        temp = temp->next;
    }
}

template <typename T>
void LinkedList<T>::printReverse() const
{
    Node* temp = tail;
    while(temp != nullptr)
    {
        cout << temp->data;
        temp = temp->prev;
    }
}

//Implementing the Big Five

//move assignment
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept
{
    if(this == &other)
    {
        return *this;
    }
    Clear();

    count = other.count;
    head = other.head;
    tail = other.tail;

    other.count = 0;
    other.head = nullptr;
    other.tail = nullptr;

    return *this;

}

//copy assignment
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
    if(this == &rhs)
    {
        return *this;
    }

    Clear();

    if(rhs.head == nullptr)
    {
        return *this;
    }

    Node* temp = rhs.head;
    while(temp != nullptr)
    {
       this->addTail(temp->data);
       temp = temp->next;
    }
    return *this;
}

//constructor
template <typename T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

//copy constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
    Node* temp = list.head;
    while(temp != nullptr)
    {
        this->addTail(temp->data);
        temp = temp->next;
    }
}

//move constructor
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept
{
    count = other.count;
    head = other.head;
    tail = other.tail;

    other.count = 0;
    other.head = nullptr;
    other.tail = nullptr;
}

//destructor
template <typename T>
LinkedList<T>::~LinkedList()
{
    Clear();
}