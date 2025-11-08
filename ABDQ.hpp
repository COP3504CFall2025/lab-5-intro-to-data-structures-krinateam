#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ();
    explicit ABDQ(std::size_t capacity);
    ABDQ(const ABDQ& other);
    ABDQ(ABDQ&& other) noexcept;
    ABDQ& operator=(const ABDQ& other);
    ABDQ& operator=(ABDQ&& other) noexcept;
    ~ABDQ();

    // Insertion
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Deletion
    T popFront() override;
    T popBack() override;

    // Access
     T& front() const override;
     T& back() const override;

    // Getters
    std::size_t getSize() const noexcept override;

    void ensureCapacity();
    void shrinkIfNeeded();
};

template <typename T>
void ABDQ<T>::pushFront(const T& item)
{
    if(size_ == capacity_) {
        T *newArray = new T[capacity_ * SCALE_FACTOR];
        for(int i = 0; i < size_; i++)
        {
            newArray[i] = data_[(front_ + i) % capacity_];
        }

        delete[] data_;
        data_ = newArray;
        capacity_ = capacity_ * SCALE_FACTOR;
        front_ = 0;
        back_ = size_;
    }
    if(front_ == 0)
    {
        front_ = capacity_;
    }
    else
    {
        front_ = front_ - 1;
    }

    size_+= 1;
    data_[front_] = item;
}

template <typename T>
void ABDQ<T>::pushBack(const T& item)
{
    if(size_ == capacity_) {
        T *newArray = new T[capacity_ * SCALE_FACTOR];
        for(int i = 0; i < size_; i++)
        {
            newArray[i] = data_[(front_ + i) % capacity_];
        }

        delete[] data_;
        data_ = newArray;
        capacity_ = capacity_ * SCALE_FACTOR;
        front_ = 0;
        back_ = size_;
    }

    data_[back_] = item;
    size_+= 1;
    if(back_ == (capacity_ - 1))
    {
        back_ = 0;
    }
    else
    {
        back_ = back_ + 1;
    }
}

template <typename T>
T ABDQ<T>::popFront()
{
    if(size_ == 0)
    {
        throw std::runtime_error("Cannot pop element because empty.");
    }
    else
    {
        size_-= 1;
        T random = data_[front_];
        if(front_ == (capacity_ - 1))
        {
            front_ = 0;
        }
        else
        {
            front_ = front_ + 1;
        }
        return random;
    }
}

template <typename T>
T ABDQ<T>::popBack()
{
    if(size_ == 0)
    {
        throw std::runtime_error("Cannot pop element because empty.");
    }
    else
    {
        size_-= 1;
        if(back_ == 0)
        {
            back_ = capacity_ - 1;
        }
        else
        {
            back_ = back_ - 1;
        }
        T random = data_[back_];
        return random;
    }
}

template <typename T>
T& ABDQ<T>::front() const
{
    if(size_ == 0)
    {
        throw std::runtime_error("Cannot find front because empty.");
    }

    return data_[front_];
}

template <typename T>
T& ABDQ<T>::back() const
{
    if(size_ == 0)
    {
        throw std::runtime_error("Cannot find back because empty.");
    }

    if(back_ == 0)
    {
        return data_[capacity_ - 1];
    }
    else
    {
        return data_[back_ - 1];
    }
}

template <typename T>
std::size_t ABDQ<T>::getSize() const noexcept
{
    return size_;
}

template <typename T>
void ABDQ<T>::ensureCapacity()
{
    if(size_ == capacity_) {
        T *newArray = new T[capacity_ * SCALE_FACTOR];
        for(int i = 0; i < size_; i++)
        {
            newArray[i] = data_[(front_ + i) % capacity_];
        }

        front_ = 0;
        back_ = size_;
        delete[] data_;
        data_ = newArray;
        capacity_ = capacity_ * SCALE_FACTOR;

    }
}

template <typename T>
void ABDQ<T>::shrinkIfNeeded()
{
    if(size_ < (capacity_/4))
    {
        T *newArray = new T[capacity_ /2];
        for(int i = 0; i < size_; i++)
        {
            newArray[i] = data_[(front_ + i) % capacity_];
        }
        front_ = 0;
        back_ = size_;
        delete[] data_;
        data_ = newArray;
        capacity_ = capacity_ /2;
    }
}


//BIG FIVE

//constructor
template <typename T>
ABDQ<T>::ABDQ()
{
    capacity_ = 4;
    size_ = 0;
    front_ = 0;
    back_ = 0;
    data_ = new T[capacity_];
}

//parameterized constructor
template <typename T>
ABDQ<T>::ABDQ(std::size_t capacity)
{
    capacity_ = capacity;
    size_ = 0;
    front_ = 0;
    back_ = 0;
    data_ = new T[capacity_];
}

//copy constructor
template <typename T>
ABDQ<T>::ABDQ(const ABDQ& other)
{
    capacity_ = other.capacity_;
    size_ = other.size_;
    front_ = other.front_;
    back_ = other.back_;

    data_ = new T[capacity_];
    for(size_t i = 0; i < size_; i++)
    {
        data_[i] = other.data_[i];
    }
}

//move constructor
template <typename T>
ABDQ<T>::ABDQ(ABDQ&& other) noexcept
{
    capacity_ = other.capacity_;
    size_ = other.size_;
    front_ = other.front_;
    back_ = other.back_;
    data_ = other.data_;

    other.capacity_ = 0;
    other.size_ = 0;
    other.front_ = 0;
    other.back_ = 0;
    other.data_ = nullptr;
}

//copy assignment
template <typename T>
ABDQ<T>& ABDQ<T>::operator=(const ABDQ& other)
{
    if(this == &other)
    {
        return *this;
    }
    delete[] data_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    front_ = other.front_;
    back_ = other.back_;

    data_ = new T[capacity_];
    for(size_t i = 0; i < size_; i++)
    {
        data_[i] = other.data_[i];
    }

    return *this;
}

//move assignment
template <typename T>
ABDQ<T>& ABDQ<T>::operator=(ABDQ&& other) noexcept
{
    if(this == &other)
    {
        return *this;
    }
    delete[] data_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    front_ = other.front_;
    back_ = other.back_;
    data_ = other.data_;

    other.capacity_ = 0;
    other.size_ = 0;
    other.front_ = 0;
    other.back_ = 0;
    other.data_ = nullptr;
    return *this;
}

//destructor
template <typename T>
ABDQ<T>::~ABDQ()
{
    delete[] data_;
    capacity_ = 0;
    size_ = 0;
    front_ = 0;
    back_ = 0;

}