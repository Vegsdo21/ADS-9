// Copyright 2022 NNTU-CS
#include "three.h"

std::vector<std::vector<char>> bruteGenerate(const TreeForm& t) {
  return t.getAll();
}

std::vector<char> indexedBrute(const TreeForm& t, int idx) {
  if (idx <= 0) return {};
  auto perms = t.getAll();
  if (idx > static_cast<int>(perms.size()))
    return {};
  return perms[idx - 1];
}

bool followIndex(Leaf* node, std::vector<char>& track, int desired, int& counter) {
  track.push_back(node->data);

  if (node->paths.empty()) {
    if (counter == desired) {
      return true;
    } else {
      ++counter;
      track.pop_back();
      return false;
    }
  }

  for (auto* next : node->paths) {
    if (followIndex(next, track, desired, counter))
      return true;
  }

  track.pop_back();
  return false;
}

std::vector<char> indexedSmart(const TreeForm& t, int idx) {
  if (idx <= 0) return {};
  int counter = 1;
  std::vector<char> route;
  Leaf* start = t.root();

  for (auto* child : start->paths) {
    if (followIndex(child, route, idx, counter)) {
      return route;
    }
  }

  return {};
}
