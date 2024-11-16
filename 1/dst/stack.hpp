#ifndef STACK_H
#define STACK_H

#include "slist.hpp"

template <typename T>
class Stack: public SList<T> {
public:
    Stack() {}

    void push(const T& value) {
        this->pushForward(value);
    }

    T pop() {
        if (this->getHead() == nullptr) {
            throw runtime_error("Stack is empty");
        }
        T popped = this->getHead()->value;
        this->removeForward();
        return popped;
    }
private:
    using SList<T>::pushBack;
    using SList<T>::pushForward;
    using SList<T>::removeBack;
    using SList<T>::removeValue;
    using SList<T>::findByValue;
    using SList<T>::get;
};

#endif
