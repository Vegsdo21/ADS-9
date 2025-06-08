// Copyright 2022 NNTU-CS
#include "tree.h"
#include <vector>

std::vector<std::vector<char>> bruteGenerate(const PMTree& tree) {
    return tree.getAllPermutations();
}

std::vector<char> indexedBrute(const PMTree& tree, int num) {
    std::vector<std::vector<char>> perms = tree.getAllPermutations();
    if (num < 0 || num >= (int)perms.size()) {
        return {};
    }
    return perms[num];
}

bool findNthPath(NodePM* node, std::vector<char>& path, int desired, int& current) {
    path.push_back(node->value);

    if (node->children.empty()) {
        if (current == desired) {
            return true;
        }
        ++current;
    } else {
        for (NodePM* child : node->children) {
            if (findNthPath(child, path, desired, current)) {
                return true;
            }
        }
    }

    path.pop_back();
    return false;
}

std::vector<char> indexedSmart(const PMTree& tree, int num) {
    std::vector<char> result;
    int current = 0;
    for (NodePM* child : tree.getRoot()->children) {
        if (findNthPath(child, result, num, current)) {
            return result;
        }
    }
    return {};
}
