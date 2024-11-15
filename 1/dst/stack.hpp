#ifndef STACK_H
#define STACK_H

#include "slist.hpp"

template <typename T>
struct Stack {
private:
    SList<T> list;

public:
    Stack() {}

    int size() const {
        return list.size();
    }

    SList<T> data() const {
        return list;
    }

    void push(const T& value) {
        list.pushForward(value);
    }

    T pop() {
        if (list.getHead() == nullptr) {
            throw runtime_error("Stack is empty");
        }
        T popped = list.getHead()->value;
        list.removeForward();
        return popped;
    }
};

#endif
