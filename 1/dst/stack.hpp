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
        if (list.head == nullptr) {
            throw runtime_error("Stack is empty");
        }
        T popped = list.head->value;
        list.removeForward();
        return popped;
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Stack<T>& stack) {
    os << stack.data() << endl;
    return os;
}

#endif
