// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <vector>
#include <chrono>

std::vector<std::vector<char>> bruteGenerate(const TreeForm& tree);
std::vector<char> indexedBrute(const TreeForm& tree, int idx);
std::vector<char> indexedSmart(const TreeForm& tree, int idx);

void printPermutation(const std::vector<char>& perm) {
    for (char c : perm)
        std::cout << c;
    std::cout << '\n';
}

int main() {
    std::vector<char> elements = {'A', 'B', 'C'};
    TreeForm tree(elements);

    for (const auto& perm : tree.getAllPermutations())
        printPermutation(perm);

    for (int i = 0; i < 6; ++i)
        printPermutation(indexedBrute(tree, i));

    for (int i = 0; i < 6; ++i)
        printPermutation(indexedSmart(tree, i));

    std::vector<char> biggerSet = {'1', '2', '3', '4', '5'};
    TreeForm bigTree(biggerSet);

    auto start = std::chrono::high_resolution_clock::now();
    auto allPerms = bigTree.getAllPermutations();
    auto finish = std::chrono::high_resolution_clock::now();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 120; ++i)
        indexedBrute(bigTree, i);
    finish = std::chrono::high_resolution_clock::now();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 120; ++i)
        indexedSmart(bigTree, i);
    finish = std::chrono::high_resolution_clock::now();

    return 0;
}
