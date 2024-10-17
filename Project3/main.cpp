#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <filesystem>  // For creating directory
#include "AVLTree.h"
#include "BinarySearchTree.h"
#include "SplayTree.h"
#include <random>

void printDepths(const BinarySearchTree<int>& bst, const std::vector<int>& testValues) {
    for (const auto& value : testValues) {
        int depth = 0;
        int result = bst.find(value, depth);
        std::cout << "Value: " << value << ", Depth: " << depth << std::endl;
    }
}

int main() {
    // Create trees
    BinarySearchTree<int> bst;
    AVLTree<int> avl;
    SplayTree<int> splay;

    // Insert values 1-100 in order
    for (int i = 1; i <= 100; ++i) {
        bst.add(i);
        avl.add(i);
        splay.add(i);
    }

    // Create the directory if it doesn't exist
    std::filesystem::create_directories("data");

    // Open file to record depths
    std::ofstream file("data/movies.csv");
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Find values 1-100 and record depths
    for (int i = 1; i <= 100; ++i) {
        int depthBST = 0, depthAVL = 0, depthSplay = 0;

        // Find in BST
        bst.find(i, depthBST);
        // Find in AVL Tree
        avl.find(i, depthAVL);
        // Find in Splay Tree
        splay.find(i, depthSplay);

        // Write depths to file
        file << "Value: " << i << ", BST Depth: " << depthBST
             << ", AVL Depth: " << depthAVL
             << ", Splay Depth: " << depthSplay << std::endl;
    }
    file.close();

    // For understanding: test with values 0, 101, 102
    std::vector<int> testValues = {0, 101, 102};
    printDepths(bst, testValues);

    // Insert random order and find in random trees
    std::vector<int> randomValues(100);
    std::iota(randomValues.begin(), randomValues.end(), 1); // Fill with 1-100
    std::shuffle(randomValues.begin(), randomValues.end(), std::mt19937{std::random_device{}()});

    for (const int value : randomValues) {
        bst.add(value);
        avl.add(value);
        splay.add(value);
    }

    // Find values 1-100 again after random insertions
    std::ofstream randomFile("data/depths.txt");
    if (!randomFile) {
        std::cerr << "Error opening depths file!" << std::endl;
        return 1;
    }
    for (int i = 1; i <= 100; ++i) {
        int depthBST = 0, depthAVL = 0, depthSplay = 0;

        // Find in BST
        bst.find(i, depthBST);
        // Find in AVL Tree
        avl.find(i, depthAVL);
        // Find in Splay Tree
        splay.find(i, depthSplay);

        // Write depths to random file
        randomFile << "Value: " << i << ", BST Depth: " << depthBST
                   << ", AVL Depth: " << depthAVL
                   << ", Splay Depth: " << depthSplay << std::endl;
    }
    randomFile.close();

    return 0;
}
