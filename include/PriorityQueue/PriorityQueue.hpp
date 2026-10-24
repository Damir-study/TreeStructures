#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <cstddef>
#include "../Abstract/IPriorityQueueStorage.hpp"

template <typename T>
class PriorityQueue {
private:
    IPriorityQueueStorage<T>* storage;

public:
    PriorityQueue(IPriorityQueueStorage<T>* storage);
    ~PriorityQueue();

    PriorityQueue(const PriorityQueue& other);
    PriorityQueue& operator=(const PriorityQueue& other);
    PriorityQueue(PriorityQueue&& other) noexcept;
    PriorityQueue& operator=(PriorityQueue&& other) noexcept;

    void push(const T& value);
    const T& top() const;
    T pop();

    bool contains(const T& value) const;
    bool empty() const;
    std::size_t get_size() const;
    void clear();
};

#include "../../src/PriorityQueue/PriorityQueue.tpp"

#endif // PRIORITY_QUEUE_HPP
