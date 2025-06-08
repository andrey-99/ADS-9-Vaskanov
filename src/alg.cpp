// Copyright 2022 NNTU-CS
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <locale>

#include "tree.h"

PMTree::PMTree(const std::vector<char>& in) : input(in) {
  root = new Node(0);
  for (char c : in) {
    std::vector<char> rest = in;
    rest.erase(std::find(rest.begin(), rest.end(), c));
    Node* child = buildTree(rest);
    child->value = c;
    root->children.push_back(child);
  }
}

PMTree::~PMTree() { deleteTree(root); }

PMTree::Node* PMTree::buildTree(const std::vector<char>& elems) {
  if (elems.empty()) return new Node(0);
  Node* localRoot = new Node(0);
  for (char c : elems) {
    std::vector<char> rest = elems;
    rest.erase(std::find(rest.begin(), rest.end(), c));
    Node* child = buildTree(rest);
    child->value = c;
    localRoot->children.push_back(child);
  }
  return localRoot;
}

void PMTree::deleteTree(Node* node) {
  if (!node) return;
  for (auto child : node->children) {
    deleteTree(child);
  }
  delete node;
}

void dfs(PMTree::Node* node, std::vector<char>& path,
         std::vector<std::vector<char>>& result, int depth, int targetLen) {
  if (depth == targetLen) {
    result.push_back(path);
    return;
  }
  for (auto child : node->children) {
    path.push_back(child->value);
    dfs(child, path, result, depth + 1, targetLen);
    path.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> path;
  int n = tree.input.size();
  for (auto child : tree.root->children) {
    path.push_back(child->value);
    dfs(child, path, result, 1, n);
    path.pop_back();
  }
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto perms = getAllPerms(tree);
  if (num <= 0 || num > static_cast<int>(perms.size())) return {};
  return perms[num - 1];
}

size_t factorial(int n) {
  size_t res = 1;
  for (int i = 2; i <= n; ++i) res *= i;
  return res;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  int n = tree.input.size();
  if (num <= 0 || num > static_cast<int>(factorial(n))) return {};
  std::vector<char> elems = tree.input;
  std::sort(elems.begin(), elems.end());
  std::vector<char> result;
  --num;
  for (int i = n; i > 0; --i) {
    size_t f = factorial(i - 1);
    int idx = num / f;
    num %= f;
    result.push_back(elems[idx]);
    elems.erase(elems.begin() + idx);
  }
  return result;
}
