#include <iostream>
#include "../dst/map.hpp"
#include "../dst/dlist.hpp"
#include "../dst/array.hpp"
#include "../dst/avl.hpp"
#include "../dst/queue.hpp"
#include "../dst/slist.hpp"
#include "../dst/stack.hpp"

void mapIllustrate() {
    Map<int> map;
    
    for (int i = 0; i < 10; i++) {
        map.put("key"+to_string(i), i + 1);
    }
    map.serialize("map.bin");

    Map<int> deserializedMap;
    deserializedMap.deserialize("map.bin");
    cout << deserializedMap << endl;
}

void dlistIllustrate() {
    DList<int> list;
    
    for (int i = 0; i < 10; i++) {
        list.pushBack(i);
    }
    list.serialize("dlist.bin");

    DList<int> deserializedList;
    deserializedList.deserialize("dlist.bin");
    cout << deserializedList << endl;
}

void avlIllustrate() {
    AVLTree avl;

    avl.insert(1);
    avl.insert(2);
    avl.insert(3);

    avl.serialize("avl.bin");

    AVLTree avl2;
    avl2.deserialize("avl.bin");
    cout << avl2 << endl;
}

void arrayIllustrate() {
    Array<int> arr;

    for (int i = 0; i < 10; i++) {
        arr.pushBack(i);
    }

    arr.serialize("array.bin");

    Array<int> deserializedArr;
    deserializedArr.deserialize("array.bin");
    cout << deserializedArr << endl;
}

void queueIllustrate() {
    Queue<int> queue;

    for (int i = 0; i < 10; i++) {
        queue.enqueue(i);
    }
    queue.serialize("queue.bin");
    Queue<int> deserializedQueue;
    deserializedQueue.deserialize("queue.bin");
    cout << deserializedQueue << endl;
}

void slistIllustrate() {
    SList<int> slist;

    for (int i = 0; i < 10; i++) {
        slist.pushBack(i);
    }
    slist.serialize("slist.bin");

    SList<int> deserializedSlist;
    deserializedSlist.deserialize("slist.bin");
    cout << deserializedSlist << endl;
}

void stackIllustrate() {
    Stack<int> stack;

    for (int i = 0; i < 10; i++) {
        stack.push(i);
    }
    stack.serialize("stack.bin");
    Stack<int> deserializedStack;
    deserializedStack.deserialize("stack.bin");
    cout << deserializedStack << endl;
}

int main() {
    stackIllustrate();

    return 0;
}