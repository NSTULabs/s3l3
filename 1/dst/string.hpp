#ifndef STRING_H
#define STRING_H
#include <iostream>
#include "array.hpp"

using namespace std;

Array<string> split(string str, char delimiter) {
    Array<string> arr;
    int lastSpace = -1;

    for (int i = 0; i < str.size(); i++) {
        if(str[i] == delimiter) {
            arr.pushBack(str.substr(lastSpace+1, i-lastSpace-1));
            lastSpace = i;
        }
    }
    arr.pushBack(str.substr(lastSpace+1, str.size()-lastSpace));

    return arr;
}

string join(const Array<string>& array, char delimiter) {
    string result;
    for (int i = 0; i < array.size(); i++) {
        result += array.get(i);
        if (i < array.size() - 1) {
            result += delimiter;
        }
    }
    return result;
}

#endif
