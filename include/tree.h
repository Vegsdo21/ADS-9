// Copyright 2025 YourName
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <algorithm>
#include <iostream>
#include <vector>

struct NodePM {
  char value;
  std::vector<NodePM*> children;

  explicit NodePM(char val) : value(val) {}
};

class PMTree {
 private:
  NodePM* root_;

  std::vector<char> removeChar(const std::vector<char>* list, char item) {
    std::vector<char> res;
    int n = list->size();
    for (int i = 0; i < n; ++i) {
      if ((*list)[i] != item) {
        res.push_back((*list)[i]);
      }
    }
    return res;
  }

  void buildTree(NodePM* node, std::vector<char> remaining) {
    int n = remaining.size();
    for (int i = 0; i < n; ++i) {
      char c = remaining[i];
      NodePM* child = new NodePM(c);
      node->children.push_back(child);
      buildTree(child, removeChar(&remaining, c));
    }
  }

  void clearTree(NodePM* node) {
    if (!node) return;
    int n = node->children.size();
    for (int i = 0; i < n; ++i) {
      clearTree(node->children[i]);
      delete node->children[i];
    }
  }

  void collectPaths(NodePM* node, std::vector<char>& path,
                    std::vector<std::vector<char>>& result) const {
    path.push_back(node->value);

    if (node->children.empty()) {
      result.push_back(path);
    } else {
      int n = node->children.size();
      for (int i = 0; i < n; ++i) {
        collectPaths(node->children[i], path, result);
      }
    }

    path.pop_back();
  }

 public:
  explicit PMTree(const std::vector<char>& chars) : root_(new NodePM('*')) {
    if (chars.empty()) return;

    std::vector<char> sorted = chars;
    std::sort(sorted.begin(), sorted.end());

    int n = sorted.size();
    for (int i = 0; i < n; ++i) {
      NodePM* child = new NodePM(sorted[i]);
      root_->children.push_back(child);
      buildTree(child, removeChar(&sorted, sorted[i]));
    }
  }

  ~PMTree() {
    clearTree(root_);
    delete root_;
  }

  std::vector<std::vector<char>> getAllPermutations() const {
    std::vector<std::vector<char>> result;
    std::vector<char> path;

    int n = root_->children.size();
    for (int i = 0; i < n; ++i) {
      collectPaths(root_->children[i], path, result);
    }

    return result;
  }

  NodePM* getRoot() const { return root_; }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
bool findNthPath(NodePM* node, std::vector<char>& path, int target, int& current);

#endif  // INCLUDE_TREE_H_
