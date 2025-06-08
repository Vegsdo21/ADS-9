// Copyright 2022 NNTU-CS
#ifndef THREE_H_
#define THREE_H_

#include <vector>
#include <algorithm>

struct Leaf {
  char data;
  std::vector<Leaf*> paths;

  explicit Leaf(char d) : data(d) {}
};

class TreeForm {
 private:
  Leaf* origin;

  std::vector<char> removeChar(const std::vector<char>& list, char ch) {
    std::vector<char> result;
    for (char c : list)
      if (c != ch)
        result.push_back(c);
    return result;
  }

  void grow(Leaf* current, const std::vector<char>& leftover) {
    for (char ch : leftover) {
      Leaf* next = new Leaf(ch);
      current->paths.push_back(next);
      grow(next, removeChar(leftover, ch));
    }
  }

  void purge(Leaf* current) {
    if (!current) return;
    for (auto* branch : current->paths) {
      purge(branch);
      delete branch;
    }
  }

  void collect(Leaf* current, std::vector<char>& trace, std::vector<std::vector<char>>& results) const {
    trace.push_back(current->data);
    if (current->paths.empty()) {
      results.push_back(trace);
    } else {
      for (auto* sub : current->paths) {
        collect(sub, trace, results);
      }
    }
    trace.pop_back();
  }

 public:
  explicit TreeForm(const std::vector<char>& elements) {
    origin = new Leaf('*');
    if (elements.empty()) return;

    std::vector<char> sorted = elements;
    std::sort(sorted.begin(), sorted.end());

    for (char ch : sorted) {
      Leaf* next = new Leaf(ch);
      origin->paths.push_back(next);
      grow(next, removeChar(sorted, ch));
    }
  }

  ~TreeForm() {
    purge(origin);
    delete origin;
  }

  std::vector<std::vector<char>> getAll() const {
    std::vector<std::vector<char>> output;
    std::vector<char> buffer;
    for (auto* branch : origin->paths) {
      collect(branch, buffer, output);
    }
    return output;
  }

  Leaf* root() const { return origin; }
};

std::vector<std::vector<char>> bruteGenerate(const TreeForm& t);
std::vector<char> indexedBrute(const TreeForm& t, int idx);
std::vector<char> indexedSmart(const TreeForm& t, int idx);
bool followIndex(Leaf* node, std::vector<char>& track, int desired, int& counter);

#endif  // THREE_H_
