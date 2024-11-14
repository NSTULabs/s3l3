#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

using namespace std;

template <typename T>
class Array {
private:
    T* data;
    int len;
    int cap;
    float loadFactor;

public:
    Array() {
        len = 0;
        cap = 16;
        data = new T[cap];
        loadFactor = 0.50;
    }

    int size() const {
        return len;
    }

    int capacity() const {
        return cap;
    }

    T* getData() const {
        return data;
    }

    void pushBack(T val) {
        if (len/cap >= loadFactor) {
            extend(cap * 2);
        }
        data[len] = val;
        len++;
    }

    void insert(int index, T val) {
        if (index < 0 || index >= len) {
            throw invalid_argument("Invalid index");
        }
        if ((float)len/cap >= loadFactor) {
            extend(cap * 2);
        }

        for (int i = len; i > index; i--) {
            data[i] = data[i-1];
        }
        data[index] = val;
        len++;
    }

    T get(int index) const {
        if (index < 0 || index >= len) {
            throw invalid_argument("Invalid index");
        }

        return data[index];
    }

    void remove(int index) {
        if (index < 0 || index >= len) {
            throw invalid_argument("Invalid index");
        }

        for (int i = index; i < len - 1; i++) {
            data[i] = data[i+1];
        }
        len--;
    }

    void set(int index, T val) {
        if (index < 0 || index >= len) {
            throw invalid_argument("Invalid index");
        }

        data[index] = val;
    }

    void extend(int newCap) {
        cap = newCap;
        T* newData = new T[cap];
        for (int i = 0; i < len; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    void reverse() {
        for (int i = 0; i < len / 2; i++) {
            T temp = data[i];
            data[i] = data[len - i - 1];
            data[len - i - 1] = temp;
        }
    }

    T& operator[](int index) {
        if (index < 0 || index >= len) {
            throw invalid_argument("Invalid index");
        }
        return data[index];
    }

};

template <typename T>
ostream& operator<<(ostream& os, const Array<T>& array) {
    auto data = array.getData();
    for (int i = 0; i < array.size(); i++) {
        os << data[i] << " ";
    }
    return os;
}

#endif
