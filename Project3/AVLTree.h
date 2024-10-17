#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

template <typename Comparable>
class AVLTree {
private:
    struct AVLNode {
        Comparable element;
        AVLNode* left;
        AVLNode* right;
        int height;

        AVLNode(const Comparable& theElement, AVLNode* lt = nullptr, AVLNode* rt = nullptr)
            : element(theElement), left(lt), right(rt), height(0) {}
    };

    AVLNode* root;

    int height(AVLNode* t) const {
        return t == nullptr ? -1 : t->height;
    }

    void updateHeight(AVLNode* t) {
        if (t != nullptr) {
            t->height = std::max(height(t->left), height(t->right)) + 1;
        }
    }

    int balanceFactor(AVLNode* t) const {
        return height(t->left) - height(t->right);
    }

    AVLNode* rotateWithLeftChild(AVLNode* k2) {
        AVLNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        updateHeight(k2);
        updateHeight(k1);
        return k1;
    }

    AVLNode* rotateWithRightChild(AVLNode* k1) {
        AVLNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        updateHeight(k1);
        updateHeight(k2);
        return k2;
    }

    AVLNode* doubleWithLeftChild(AVLNode* k3) {
        k3->left = rotateWithRightChild(k3->left);
        return rotateWithLeftChild(k3);
    }

    AVLNode* doubleWithRightChild(AVLNode* k1) {
        k1->right = rotateWithLeftChild(k1->right);
        return rotateWithRightChild(k1);
    }

    AVLNode* insert(const Comparable& x, AVLNode* t) {
        if (t == nullptr) {
            return new AVLNode(x);
        } else if (x < t->element) {
            t->left = insert(x, t->left);
        } else if (t->element < x) {
            t->right = insert(x, t->right);
        }
        updateHeight(t);
        return balance(t);
    }

    AVLNode* balance(AVLNode* t) {
        if (balanceFactor(t) == 2) {
            if (balanceFactor(t->left) == 1) {
                return rotateWithLeftChild(t);
            } else {
                return doubleWithLeftChild(t);
            }
        } else if (balanceFactor(t) == -2) {
            if (balanceFactor(t->right) == -1) {
                return rotateWithRightChild(t);
            } else {
                return doubleWithRightChild(t);
            }
        }
        return t;  // Balanced
    }

public:
    AVLTree() : root(nullptr) {}

    void add(const Comparable& c) {
        root = insert(c, root);
    }

    int find(const Comparable& x, int& depth) const {
        AVLNode* t = root;
        depth = 0;  // Start at root (depth 0)
        while (t != nullptr) {
            if (x < t->element) {
                t = t->left;
                ++depth;
            } else if (t->element < x) {
                t = t->right;
                ++depth;
            } else {
                return depth;  // Found the element
            }
        }
        return 100;  // Element not found
    }
};

#endif // AVLTREE_H
