#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "dlist.hpp"

using namespace std;


template <typename T>
class Queue: public DList<T> {
public:
    Queue() {}

    void enqueue(const T& val) {
        this->pushBack(val);
    }

    T dequeue() {
        if (this->size() == 0) {
            throw runtime_error("Queue is empty");
        }

        T dequeued = this->getHead()->value;
        this->removeForward();
        return dequeued;
    }
private:
    using DList<T>::pushBack;
    using DList<T>::pushForward;
    using DList<T>::removeBack;
    using DList<T>::removeValue;
    using DList<T>::findByValue;
    using DList<T>::get;
};

#endif
