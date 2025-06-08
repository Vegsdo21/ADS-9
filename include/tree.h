#ifndef INCLUDE_PERMTREE_H_
#define INCLUDE_PERMTREE_H_

#include <vector>
#include <algorithm>

struct Node {
  char symbol;
  std::vector<Node*> branches;

  explicit Node(char s) : symbol(s) {}
};

class PermTree {
 private:
  Node* base;

  std::vector<char> exclude(const std::vector<char>& source, char ch) {
    std::vector<char> output;
    for (char c : source)
      if (c != ch)
        output.push_back(c);
    return output;
  }

  void expand(Node* current, const std::vector<char>& rest) {
    for (char ch : rest) {
      Node* child = new Node(ch);
      current->branches.push_back(child);
      expand(child, exclude(rest, ch));
    }
  }

  void cleanup(Node* current) {
    if (!current) return;
    for (auto* b : current->branches) {
      cleanup(b);
      delete b;
    }
  }

  void gather(Node* current, std::vector<char>& temp, std::vector<std::vector<char>>& storage) const {
    temp.push_back(current->symbol);

    if (current->branches.empty()) {
      storage.push_back(temp);
    } else {
      for (auto* b : current->branches) {
        gather(b, temp, storage);
      }
    }

    temp.pop_back();
  }

 public:
  explicit PermTree(const std::vector<char>& input) {
    base = new Node('*');
    if (input.empty()) return;

    std::vector<char> sorted = input;
    std::sort(sorted.begin(), sorted.end());

    for (char ch : sorted) {
      Node* child = new Node(ch);
      base->branches.push_back(child);
      expand(child, exclude(sorted, ch));
    }
  }

  ~PermTree() {
    cleanup(base);
    delete base;
  }

  std::vector<std::vector<char>> allPermutations() const {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    for (auto* child : base->branches) {
      gather(child, path, result);
    }
    return result;
  }

  Node* getBase() const { return base; }
};

std::vector<std::vector<char>> generatePerms(const PermTree& tree);
std::vector<char> getByIndexFull(const PermTree& tree, int index);
std::vector<char> getByIndexTree(const PermTree& tree, int index);
bool findPathByIndex(Node* node, std::vector<char>& path, int goal, int& counter);

#endif  // INCLUDE_PERMTREE_H_
