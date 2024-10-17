#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>

template <typename Comparable>
class SplayTree {
private:
    struct SplayNode {
        Comparable element;
        SplayNode* left;
        SplayNode* right;

        SplayNode(const Comparable& theElement, SplayNode* lt = nullptr, SplayNode* rt = nullptr)
            : element(theElement), left(lt), right(rt) {}
    };

    SplayNode* root;

    // Splay function that rearranges the tree and keeps track of depth
    SplayNode* splay(const Comparable& x, SplayNode* t, int& depth) {
        if (t == nullptr) {
            return nullptr;
        }
        if (x < t->element) {
            if (t->left == nullptr) return t;
            depth++;
            if (x < t->left->element) {
                t->left->left = splay(x, t->left->left, depth);
                t = rotateWithRightChild(t);
            } else if (x > t->left->element) {
                t->left->right = splay(x, t->left->right, depth);
                if (t->left->right != nullptr)
                    t->left = rotateWithLeftChild(t->left);
            }
            return t->left == nullptr ? t : rotateWithRightChild(t);
        } else if (t->element < x) {
            if (t->right == nullptr) return t;
            depth++;
            if (t->right->element < x) {
                t->right->right = splay(x, t->right->right, depth);
                t = rotateWithLeftChild(t);
            } else if (x < t->right->element) {
                t->right->left = splay(x, t->right->left, depth);
                if (t->right->left != nullptr)
                    t->right = rotateWithRightChild(t->right);
            }
            return t->right == nullptr ? t : rotateWithLeftChild(t);
        }
        return t;  // Found
    }

    SplayNode* rotateWithLeftChild(SplayNode* k2) {
        if (k2 == nullptr || k2->left == nullptr) return k2;
        SplayNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        return k1;
    }

    SplayNode* rotateWithRightChild(SplayNode* k1) {
        if (k1 == nullptr || k1->right == nullptr) return k1;
        SplayNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        return k2;
    }

    SplayNode* insert(const Comparable& x, SplayNode* t) {
        int depth = 0;
        if (t == nullptr) {
            return new SplayNode(x);
        }
        t = splay(x, t, depth);
        if (t->element == x) {
            return t;  // Duplicate
        }
        SplayNode* newNode = new SplayNode(x);
        if (x < t->element) {
            newNode->right = t;
            newNode->left = t->left;
            t->left = nullptr;
        } else {
            newNode->left = t;
            newNode->right = t->right;
            t->right = nullptr;
        }
        return newNode;
    }

public:
    SplayTree() : root(nullptr) {}

    void add(const Comparable& c) {
        root = insert(c, root);
    }

    int find(const Comparable& x, int& depth) {
        root = splay(x, root, depth);
        if (root == nullptr || root->element != x) {
            return 100;  // Element not found
        }
        return depth;  // Found at root
    }
};

#endif // SPLAYTREE_H
