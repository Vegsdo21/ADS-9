// Copyright 2022 NNTU-CS
#include "tree.h"
#include <vector>

std::vector<std::vector<char>> bruteGenerate(const PMTree& tree) {
    return tree.getAllPermutations();
}

std::vector<char> indexedBrute(const PMTree& tree, int idx) {
    auto perms = tree.getAllPermutations();
    if (idx < 0 || idx >= static_cast<int>(perms.size())) {
        return {};
    }
    return perms[idx];
}

bool followIndex(NodePM* node, std::vector<char>& path, int desired, int& counter) {
    path.push_back(node->value);
    if (node->children.empty()) {
        if (counter == desired) {
            return true;
        }
        ++counter;
    } else {
        for (NodePM* child : node->children) {
            if (followIndex(child, path, desired, counter)) {
                return true;
            }
        }
    }
    path.pop_back();
    return false;
}

std::vector<char> indexedSmart(const PMTree& tree, int idx) {
    std::vector<char> result;
    int counter = 0;
    NodePM* root = tree.getRoot();
    for (NodePM* child : root->children) {
        if (followIndex(child, result, idx, counter)) {
            return result;
        }
    }
    return {};
}
