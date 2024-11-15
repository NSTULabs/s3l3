#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "dlist.hpp"

using namespace std;


template <typename T>
class Queue {
private:
    DList<T> list;

public:
    Queue() {}
    
    DList<T> data() const {
        return list;
    }

    int size() const {
        return list.size();
    }

    void enqueue(const T& val) {
        list.pushBack(val);
    }

    T dequeue() {
        if (size() == 0) {
            throw runtime_error("Queue is empty");
        }

        T dequeued = list.getHead()->value;
        list.removeForward();

        return dequeued;
    }
};

#endif
