#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() = default;

    // Core Insertion Operations
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Core Removal Operations
    T popFront() override;
    T popBack() override;

    // Element Accessors
     const T& front() const override;
     const T& back() const override;

    // Getter
    std::size_t getSize() const noexcept override;
};

template <typename T>
void LLDQ<T>::pushFront(const T& item)
{
    list.addHead(item);
}

template <typename T>
void LLDQ<T>::pushBack(const T& item)
{
    list.addTail(item);
}

template <typename T>
T LLDQ<T>::popFront()
{
    if(list.getHead() == nullptr)
    {
        throw std::runtime_error("Cannot pop front b/c linked list is empty.");
    }
    T random = list.getHead()->data;
    list.removeHead();
    return random;
}

template <typename T>
T LLDQ<T>::popBack()
{
    if(list.getHead() == nullptr)
    {
        throw std::runtime_error("Cannot pop back b/c linked list is empty.");
    }
    T random = list.getTail() -> data;
    list.removeTail();
    return random;
}

template <typename T>
const T& LLDQ<T>::front() const
{
    if(list.getHead() == nullptr)
    {
        throw std::runtime_error("Cannot retrieve front data b/c linked list is empty.");
    }
    return list.getHead()->data;
}

template <typename T>
const T& LLDQ<T>::back() const
{
    if(list.getTail() == nullptr)
    {
        throw std::runtime_error("Cannot retrieve back data b/c linked list is empty.");
    }
    return list.getTail()->data;
}

template <typename T>
std::size_t LLDQ<T>::getSize() const noexcept
{
    return list.getCount();
}




