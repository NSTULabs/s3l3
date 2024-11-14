#ifndef SLIST_H
#define SLIST_H

#include <iostream>

using namespace std;

template <typename T>
struct SNode {
    T value;
    SNode<T>* next;

    SNode(const T& val) : value(val), next(nullptr) {}
};

template <typename T>
class SList {
private:
    SNode<T>* head;
    int len;

public:
    SList() {
        head = nullptr;
        len = 0;
    }

    SNode<T>* getHead() const {
        return head;
    }

    int size() const {
        return len;
    }

    void pushForward(T val) {
        SNode<T>* node = new SNode<T>(val);
        SNode<T>* oldHead = head;
        head = node;
        node->next = oldHead;
        len++;
    }

    void pushBack(T value) {
        SNode<T>* node = new SNode<T>(value);
        if (head == nullptr) {
            head = node;
            return;
        }

        SNode<T>* current = head;
        while (current->next!= nullptr) {
            current = current->next;
        }
        current->next = node;
        len++;
    }

    T get(int index) const {
        if (index < 0 || index >= len) {
            throw runtime_error("Index out of bounds");
        }

        SNode<T>* current = head;
        int c = 0;
        while (c != index && current != nullptr) {
            current = current->next;
            c++;
        }
        return current->value;
    }

    void removeForward() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        SNode<T>* oldHead = head;
        head = head->next;
        delete oldHead;
        len--;
    }

    void removeBack() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        SNode<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        delete current;
        len--;
    }

    void removeValue(const T& value) {
        SNode<T>* prev = nullptr;
        SNode<T>* current = head;

        while(current != nullptr) {
            if(current->value == value) {
                if (prev != nullptr) {
                    prev->next = current->next;
                    delete current;
                    current = prev->next;
                } else {
                    head = current->next;
                    delete current;
                    current = head;
                }
            } else {
                prev = current;
                current = current->next;
            }
        }
    }

    SNode<T>* findByValue(const T& value) {
        SNode<T>* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    string join(char delimiter) {
        string result;
        SNode<string>* current = head;

        while (current != nullptr) {
            result += current->value;
            if (current->next != nullptr) {
                result += delimiter;
            }
            current = current->next;
        }

        return result;
    }
};

template <typename T>
ostream& operator<<(ostream& os, const SList<T>& list) {
    auto head = list.getHead();
    while (head != nullptr) {
        os << head->value << " ";
        head = head->next;
    }
    return os;
}

#endif