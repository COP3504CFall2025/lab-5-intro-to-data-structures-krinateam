#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ();
    explicit ABQ(const size_t capacity);
    ABQ(const ABQ& other);
    ABQ& operator=(const ABQ& rhs);
    ABQ(ABQ&& other) noexcept;
    ABQ& operator=(ABQ&& rhs) noexcept;
    ~ABQ() noexcept;

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override;
    [[nodiscard]] size_t getMaxCapacity() const noexcept;
    //[[nodiscard]] T* getData() const noexcept;

    // Insertion
    void enqueue(const T& data) override;

    // Access
    T peek() const override;

    // Deletion
    T dequeue() override;


    void ensureCapacity();
    void shrinkIfNeeded();

};

//constructor
template<typename T>
ABQ<T>::ABQ()
{
    capacity_ = 1;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template<typename T>
ABQ<T>::ABQ(const size_t capacity)
{
    capacity_ = capacity;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

//copy constructor
template<typename T>
ABQ<T>::ABQ(const ABQ& other)
{
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;

    array_ = new T[capacity_];
    for(size_t i = 0; i < curr_size_; i++)
    {
        array_[i] = other.array_[i];
    }
}

//copy assignment
template<typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ& rhs)
{
    if(this == &rhs)
    {
        return *this;
    }
    delete[] array_;
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    for(size_t i = 0; i < curr_size_; i++)
    {
        array_[i] = rhs.array_[i];
    }
}

//move constructor
template<typename T>
ABQ<T>::ABQ(ABQ&& other) noexcept
{
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = other.array_;

    other.capacity_ = 0;
    other.curr_size_ = 0;
    other.array_ = nullptr;
}

//move assignment
template<typename T>
ABQ<T>& ABQ<T>::operator=(ABQ&& rhs) noexcept
{
    if(this == &rhs)
    {
        return *this;
    }
    delete[] array_;
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    array_ = rhs.array_;

    rhs.capacity_ = 0;
    rhs.curr_size_ = 0;
    rhs.array_ = nullptr;
    return *this;
}

//destructor
template<typename T>
ABQ<T>::~ABQ() noexcept
{
    delete[] array_;
    capacity_ = 0;
    curr_size_ = 0;
}

template<typename T>
[[nodiscard]] size_t ABQ<T>::getSize() const noexcept
{
    return curr_size_;
}

template<typename T>
[[nodiscard]] size_t ABQ<T>::getMaxCapacity() const noexcept
{
    return capacity_;
}
/*
template<typename T>
[[nodiscard]] T* ABQ<T>::getData() const noexcept
{
    return array_;
}
*/

template<typename T>
void ABQ<T>::enqueue(const T& data)
{
    if(curr_size_ == capacity_)
    {
        T* newArray = new T[capacity_ * scale_factor_];
        capacity_ = capacity_ * scale_factor_;

        for(size_t i = 0; i < curr_size_; i++)
        {
            newArray[i] = array_[i];
        }
        delete[] array_;
        array_ = newArray;
        newArray = nullptr;
    }
    array_[curr_size_] = data;
    curr_size_ += 1;
}

template<typename T>
T ABQ<T>::peek() const
{
    if(curr_size_ == 0)
    {
        throw std::runtime_error("Can't return front element because queue is empty.");
    }
    else
    {
        return array_[0];
    }
}

template<typename T>
T ABQ<T>::dequeue()
{
    if(curr_size_ == 0)
    {
        throw std::runtime_error("Can't remove front element because queue is empty.");
    }
    else
    {
        int i = 1;
        T random = array_[0];
        while(i < curr_size_)
        {
            //shifts element of array by one to remove front element.
            array_[i-1] = array_[i];
            i++;
        }

        curr_size_ = curr_size_ - 1;
        return random;
    }
}


template <typename T>
void ABQ<T>::ensureCapacity()
{
    if(curr_size_ == capacity_) {
        T *newArray = new T[capacity_ * 2];
        for(int i = 0; i < curr_size_; i++)
        {
            newArray[i] = array_[i];
        }

        delete[] array_;
        array_ = newArray;
        capacity_ = capacity_ * 2;

    }
}

template <typename T>
void ABQ<T>::shrinkIfNeeded()
{
    if(curr_size_ < (capacity_/4))
    {
        T *newArray = new T[capacity_ /2];
        for(int i = 0; i < curr_size_; i++)
        {
            newArray[i] = array_[i];
        }

        delete[] array_;
        array_ = newArray;
        capacity_ = capacity_ /2;
    }
}