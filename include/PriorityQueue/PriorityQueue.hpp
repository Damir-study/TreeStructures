#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <cstddef>
#include "../Abstract/IPriorityQueueStorage.hpp"

template <typename T>
class PriorityQueue {
public:
    using Transform = T (*)(const T&);
    using Predicate = bool (*)(const T&);
    template <typename Y>
    using Reducer = Y (*)(const T&, const Y&);

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

    PriorityQueue map(Transform transform) const;
    PriorityQueue where(Predicate predicate) const;
    template <typename Y>
    Y reduce(Reducer<Y> function, const Y& initial) const;
};

#include "../../src/PriorityQueue/PriorityQueue.tpp"

#endif // PRIORITY_QUEUE_HPP
