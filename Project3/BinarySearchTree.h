#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>

template <typename Comparable>
class BinarySearchTree {
private:
    struct BinaryNode {
        Comparable element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Comparable& theElement, BinaryNode* lt = nullptr, BinaryNode* rt = nullptr)
            : element(theElement), left(lt), right(rt) {}
    };

    BinaryNode* root;

    int find(const Comparable& x, BinaryNode* t, int& depth) const {
        if (t == nullptr) {
            return 100;  // Return 100 for not found
        } else if (x < t->element) {
            depth++;
            return find(x, t->left, depth);
        } else if (t->element < x) {
            depth++;
            return find(x, t->right, depth);
        } else {
            return depth;  // Found the element
        }
    }

    BinaryNode* insert(const Comparable& x, BinaryNode* t) {
        if (t == nullptr) {
            return new BinaryNode(x);
        } else if (x < t->element) {
            t->left = insert(x, t->left);
        } else if (t->element < x) {
            t->right = insert(x, t->right);
        }
        return t;  // Duplicate; do nothing
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void add(const Comparable& c) {
        root = insert(c, root);
    }

    int find(const Comparable& x, int& depth) const {
        return find(x, root, depth);
    }
};

#endif // BINARYSEARCHTREE_H
