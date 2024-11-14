#ifndef SET_H
#define SET_H

#include "map.hpp"


template <typename T>
class Set {
private:
    Map<T> map;
public:
    Set() {}

    MapNode<T>** getData() const {
        return map.getData();
    }

    int getLen() const {
        return map.getLen();
    }

    int getCap() const {
        return map.getCap();
    }

    bool contains(const string& key) const {
        try {
            return map.get(key);
        } catch (const runtime_error& e) {
            return false;
        }
    }

    void put(const string& key) {
        map.put(key, true);
    }

    void remove(const string& key) {
        map.remove(key);
    }

    string join() {
        string result = "";
        auto buckets = map.getData();

        for (int i = 0; i < map.getCap(); i++) {
            MapNode<T>* current = buckets[i];
            while (current != nullptr) {
                result += current->key + ",";
                current = current->next;
            }
        }
        result = result.substr(0, result.size() - 1);
        return result;
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Set<T>& set) {
    auto data = set.getData();
    for (int i = 0; i < set.getCap(); i++) {
        if (data[i] != nullptr) {
            auto current = data[i];
            os << i << ": ";
            while (current != nullptr) {
                os << current->key << " ";  // Выводим ключ текущего узла
                current = current->next;
            }
            os << endl;
        }
    }
    return os;
}

#endif
