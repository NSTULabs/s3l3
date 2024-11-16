#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <functional>
#include <fstream>

using namespace std;

struct AVLTreeNode {
    int value;
    int height;
    AVLTreeNode* left;
    AVLTreeNode* right;

    AVLTreeNode(const int val) : value(val), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    AVLTreeNode* head;
public:
    AVLTree() : head(nullptr) {}

    AVLTreeNode* getHead() const {
        return head;
    }

    int height(AVLTreeNode* node) const {
        return node == nullptr ? 0 : node->height;
    }

    void updateHeight(AVLTreeNode* node) {
        if (node != nullptr) {
            node->height = max(height(node->left), height(node->right)) + 1;
        }
    }

    void updateAllHeights(AVLTreeNode* node) {
        if (node == nullptr) {
            return;
        }

        updateAllHeights(node->left);
        updateAllHeights(node->right);

        updateHeight(node);
    }


    int getBalance(AVLTreeNode* node) {
        return node == nullptr ? 0 : height(node->left) - height(node->right);
    }

    AVLTreeNode* rotateRight(AVLTreeNode* y) {
        AVLTreeNode* x = y->left;
        AVLTreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLTreeNode* rotateLeft(AVLTreeNode* x) {
        AVLTreeNode* y = x->right;
        AVLTreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLTreeNode* balanceNode(AVLTreeNode* node) {
        updateAllHeights(head);
        int balance = getBalance(node);

        // Левое вращение, если баланс > 1 и вставка произошла в левое поддерево
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }

        // Правое вращение, если баланс < -1 и вставка произошла в правое поддерево
        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }

        // Левое-правое вращение, если баланс > 1 и вставка произошла в правое поддерево левого поддерева
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Правое-левое вращение, если баланс < -1 и вставка произошла в левое поддерево правого поддерева
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void insert(int value) {
        function<AVLTreeNode*(AVLTreeNode*, int)> insertValue = [&](AVLTreeNode* node, int value) -> AVLTreeNode* {
            if (node == nullptr) {
                return new AVLTreeNode(value);
            }

            if (value < node->value) {
                node->left = insertValue(node->left, value);
            } else if (value > node->value) {
                node->right = insertValue(node->right, value);
            } else {
                return node; // в дереве нет дубликатов
            }

            return balanceNode(node);
        };
        head = insertValue(head, value);
    }

    AVLTreeNode* getMinValueNode(AVLTreeNode* node) {
        AVLTreeNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void remove(int value) {
        function<AVLTreeNode*(AVLTreeNode*, int)> removeValue = [&](AVLTreeNode* node, int value) {
            if (node == nullptr) {
                return node;
            }

            if (value < node->value) {
                node->left = removeValue(node->left, value);
            } else if (value > node->value) {
                node->right = removeValue(node->right, value);
            } else { // узел для удаления найден
                if (node->left == nullptr || node->right == nullptr) { // если один ребёнок
                    AVLTreeNode* temp = node->left ? node->left : node->right;
                    if (temp == nullptr) { // если нет детей
                        temp = node;
                        node = nullptr;
                    } else {
                        *node = *temp;
                    }
                    delete temp;
                } else { // если два ребёнка
                    AVLTreeNode* temp = getMinValueNode(node->right); // находим минимальное справа, ставим на место удаляемого
                    node->value = temp->value;
                    node->right = removeValue(node->right, temp->value);
                }
            }
            if (node == nullptr) {
                return node;
            }

            return balanceNode(node);
        };
        head = removeValue(head, value);
    }

    AVLTreeNode* find(int value) {
        function<AVLTreeNode*(AVLTreeNode*, int)> findValue = [&](AVLTreeNode* node, int value) -> AVLTreeNode* {
            if (node == nullptr || node->value == value) {
                return node;
            }

            if (value < node->value) {
                return findValue(node->left, value);
            } else {
                return findValue(node->right, value);
            }
        };
        return findValue(head, value);
    }

    // AVLTreeNode -> string
    void serialize(const string& filename) {
        ofstream ofs(filename, ios::binary);

        function<void(AVLTreeNode*)> serializeNode = [&](AVLTreeNode* node) {
            if (node == nullptr) {
                int nullMarker = 0xFFFFFFFF;
                ofs.write(reinterpret_cast<const char*>(&nullMarker), sizeof(nullMarker));
                return;
            }


            ofs.write(reinterpret_cast<const char*>(&node->value), sizeof(node->value));

            serializeNode(node->left);
            serializeNode(node->right);
        };

        serializeNode(head);
        ofs.close();
    }

    // string -> AVLTreeNode
    void deserialize(const string& filename) {
        ifstream ifs(filename, ios::binary);
        function<AVLTreeNode*(ifstream&)> unserializeSS = [&](ifstream& ss) -> AVLTreeNode* {
            int value;
            ifs.read(reinterpret_cast<char*>(&value), sizeof(value));

            if (value == 0xFFFFFFFF) {
                return nullptr;
            }

            AVLTreeNode* node = new AVLTreeNode(value);
            node->left = unserializeSS(ss);
            node->right = unserializeSS(ss);

            return node;
        };
        head = unserializeSS(ifs);
    }
};

void printAVLTree(string& result, AVLTreeNode* node, int depth = 0, string prefix = "") {
    if (node == nullptr) {
        return;
    }
    if (node->right != nullptr) {
        printAVLTree(result, node->right, depth + 1, prefix + "\t");
    }
    result += "\n";

    result += prefix;
    result += "[" + to_string(node->value) + "]\n";

    if (node->left != nullptr) {
        printAVLTree(result, node->left, depth + 1, prefix + "\t");
    }
}

ostream& operator<<(ostream& os, const AVLTree& tree) {
    string stringTree = "";
    printAVLTree(stringTree, tree.getHead());
    os << stringTree;
    return os;
}

#endif
