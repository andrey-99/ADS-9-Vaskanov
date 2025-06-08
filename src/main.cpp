// Copyright 2022 NNTU-CS
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "tree.h"

int main() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);

  auto perms = getAllPerms(tree);
  for (auto& perm : perms) {
    for (char c : perm) std::cout << c;
    std::cout << std::endl;
  }

  std::cout << "getPerm1(1): ";
  auto p1 = getPerm1(tree, 1);
  for (char c : p1) std::cout << c;
  std::cout << std::endl;

  std::cout << "getPerm2(2): ";
  auto p2 = getPerm2(tree, 2);
  for (char c : p2) std::cout << c;
  std::cout << std::endl;

  for (int n = 3; n <= 7; ++n) {
    std::vector<char> in2;
    for (int i = 0; i < n; ++i) in2.push_back('a' + i);
    PMTree t2(in2);

    std::mt19937 gen(42);
    std::uniform_int_distribution<> dist(1, static_cast<int>(factorial(n)));

    int rnd_num = dist(gen);

    auto t0 = std::chrono::high_resolution_clock::now();
    getAllPerms(t2);
    auto t1 = std::chrono::high_resolution_clock::now();
    getPerm1(t2, rnd_num);
    auto t2_time = std::chrono::high_resolution_clock::now();
    getPerm2(t2, rnd_num);
    auto t3 = std::chrono::high_resolution_clock::now();

    double dt1 = std::chrono::duration<double>(t1 - t0).count();
    double dt2 = std::chrono::duration<double>(t2_time - t1).count();
    double dt3 = std::chrono::duration<double>(t3 - t2_time).count();

    std::cout << "n=" << n << ": getAllPerms=" << dt1 << "s getPerm1=" << dt2
              << "s getPerm2=" << dt3 << "s\n";
  }

  return 0;
}
