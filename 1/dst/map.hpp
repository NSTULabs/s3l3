#ifndef MAP_H
#define MAP_H

#include <string>
#include <iostream>
#include <cstdint>
#include <fstream>

using namespace std;

template <typename T>
struct MapNode {
    string key;
    T value;
    MapNode<T>* next;

    MapNode<T>(string k, T v) : key(k), value(v), next(nullptr) {}
};

template <typename T>
class Map {
private:
    MapNode<T>** data;
    int cap;
    int len;
    double loadFactor;

    void rehash(int newcap) {
        MapNode<T>** newMap = new MapNode<T>*[newcap];

        for (int i = 0; i < newcap; i++) {
            newMap[i] = nullptr;
        }

        for (int i = 0; i < cap; i++) {
            MapNode<T>* current = data[i];
            while (current != nullptr) {
                MapNode<T>* next = current->next;
                uint32_t newIndex = hash(current->key) % newcap;
                
                if (newMap[newIndex] == nullptr) { // бакета нет
                    current->next = nullptr;
                    newMap[newIndex] = current;
                } else { // бакет есть -> добавляем в него
                    MapNode<T>* currentNewMap = newMap[newIndex];

                    while (currentNewMap->next != nullptr) {
                        currentNewMap = currentNewMap->next;
                    }
                    current->next = nullptr;
                    currentNewMap->next = current;
                }
                current = next;
            }
        }

        delete[] data;
        data = newMap;
        cap = newcap;
    }

public:
    Map() {
        cap = 16;
        len = 0;
        loadFactor = 0.50;

        data = new MapNode<T>*[cap];

        for (int i = 0; i < cap; i++) {
            data[i] = nullptr;
        }
    }

    MapNode<T>** getData() const {
        return data;
    }

    int size() const {
        return len;
    }

    int capacity() const {
        return cap;
    }

    uint32_t hash(string key) const {
        uint32_t hash = 5381;
        for (char c : key) {
            hash = (hash << 5) + hash + c;
        }
        return hash;
    }

    void put(string key, T value) {
        if ((float)len / cap >= loadFactor) {
            rehash(cap * 2);
        }

        uint32_t index = hash(key) % cap;

        if (data[index] == nullptr) { // бакета нет
            data[index] = new MapNode<T>(key, value);
        } else { // бакет есть -> добавляем в него
            MapNode<T>* current = data[index];

            while (current->next != nullptr) {
                if (current->key == key) {
                    current->value = value;
                    return;
                }
                current = current->next;
            }
            if (current->key == key) { // check last element
                current->value = value;
                return;
            }

            current->next = new MapNode<T>(key, value);
        }

        len++;
    }

    T get(string key) const {
        uint32_t index = hash(key) % cap;

        MapNode<T>* current = data[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        throw runtime_error("Key not found");
    }

    void remove(string key) {
        uint32_t index = hash(key) % cap;

        MapNode<T>* prev = nullptr;
        MapNode<T>* current = data[index];

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    data[index] = current->next;
                    delete current;
                    len--;
                    return;
                } else {
                    prev = current->next;
                    delete current;
                    len--;
                    return;
                }
            }
            prev = current;
            current = current->next;
        }

        throw runtime_error("Key not found");
    }

    // works only with int value
    void serialize(const string& filename) {
        ofstream file(filename, ios::binary);
        if (!file.is_open()) {
            throw runtime_error("Error opening file");
        }

        file.write(reinterpret_cast<char*>(&len), sizeof(len));
        for (int i = 0; i < cap; i++) {
            MapNode<T>* current = data[i];
            while (current!= nullptr) {
                file << current->key << '\x00';
                file.write(reinterpret_cast<char*>(&current->value), sizeof(current->value));
                current = current->next;
            }
        }

        file.close();
    }

    // works only with int value
    void deserialize(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            throw runtime_error("Error opening file");
        }

        int serLen;
        file.read(reinterpret_cast<char*>(&serLen), sizeof(serLen));
        for (int i = 0; i < serLen; i++) {
            string key;
            char symbol = 0xFF;

            while (true) {
                file.read(&symbol, 1);
                if (!file) {
                    throw runtime_error("Error reading key data");
                }
                if (symbol == 0x00) {
                    break;
                }
                key += symbol;
            }

            T value;
            file.read(reinterpret_cast<char*>(&value), sizeof(value));

            put(key, value);
            cout << i << endl;
        }

        file.close();
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Map<T>& map) {
    MapNode<T>** data = map.getData();
    for (int i = 0; i < map.capacity(); i++) {
        if (data[i] != nullptr) {
            auto current = data[i];
            os << i << ": ";
            while (current!= nullptr) {
                os << current->key << " - " << current->value << ", ";
                current = current->next;
            }
            os << endl;
        }
    }
    return os;
}

#endif
