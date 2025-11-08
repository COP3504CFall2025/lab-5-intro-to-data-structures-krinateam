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
    list.addHead();
}

template <typename T>
void LLDQ<T>::pushBack(const T& item)
{
    list.getTail();
}

template <typename T>
T LLDQ<T>::popFront()
{
    list.removeHead();
}

template <typename T>
T LLDQ<T>::popBack()
{
    list.removeTail();
}

template <typename T>
const T& LLDQ<T>::front() const
{
    return list.getHead()->data;
}

template <typename T>
const T& LLDQ<T>::back() const
{
    return list.getTail()->data;
}

template <typename T>
std::size_t LLDQ<T>::getSize() const noexcept
{
    return list.getCount();
}




