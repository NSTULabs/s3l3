#ifndef SLIST_H
#define SLIST_H

#include <iostream>
#include <fstream>

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
            len++;
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
            throw runtime_error("Invalid index");
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
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        SNode<T>* prev = nullptr;
        SNode<T>* current = head;

        while(current != nullptr) {
            if(current->value == value) {
                if (prev != nullptr) {
                    prev->next = current->next;
                    delete current;
                    len--;
                    current = prev->next;
                } else {
                    head = current->next;
                    delete current;
                    len--;
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

    // works only with int
    void serialize(const string& filename) {
        ofstream ofs(filename, ios::binary);
        if (!ofs.is_open()) {
            throw runtime_error("Failed to open file");
        }

        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        SNode<T>* current = head;
        while (current!= nullptr) {
            ofs.write(reinterpret_cast<const char*>(&current->value), sizeof(current->value));
            current = current->next;
        }
    }

    // works only with int
    void deserialize(const string& filename) {
        ifstream ifs(filename, ios::binary);
        if (!ifs.is_open()) {
            throw runtime_error("Cannot open file for reading");
        }

        int size;
        ifs.read(reinterpret_cast<char*>(&size), sizeof(size));

        T value;
        for (int i = 0; i < size; i++) {
            ifs.read(reinterpret_cast<char*>(&value), sizeof(value));
            pushBack(value);
        }
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