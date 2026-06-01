// Copyright 2022 NNTU-CS
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <random>
#include <vector>
#include "tree.h"

static void printPerm(const std::vector<char>& p) {
    for (char c : p) {
        std::cout << c;
    }
    std::cout << "\n";
}

static std::vector<char> makeAlphabet(int n) {
    std::vector<char> v;
    for (int i = 0; i < n; ++i) {
        if (i < 9) {
            v.push_back(static_cast<char>('1' + i));
        } else {
            v.push_back(static_cast<char>('a' + (i - 9)));
        }
    }
    return v;
}

int main() {
    std::cout << "Example {1,2,3}\n";
    PMTree tree({'1', '2', '3'});
    auto perms = getAllPerms(tree);

    std::cout << "getAllPerms:\n";
    for (int i = 0; i < static_cast<int>(perms.size()); ++i) {
        std::cout << "  " << (i + 1) << ": ";
        printPerm(perms[i]);
    }

    std::cout << "getPerm1 #1: ";
    printPerm(getPerm1(tree, 1));

    std::cout << "getPerm1 #2: ";
    printPerm(getPerm1(tree, 2));

    std::cout << "getPerm1 #7 (out of range): ";
    auto bad = getPerm1(tree, 7);
    if (bad.empty()) {
        std::cout << "(empty)\n";
    } else {
        printPerm(bad);
    }

    std::cout << "getPerm2 #1: ";
    printPerm(getPerm2(tree, 1));

    std::cout << "getPerm2 #2: ";
    printPerm(getPerm2(tree, 2));

    std::cout << "getPerm2 #6: ";
    printPerm(getPerm2(tree, 6));

    std::cout << "\nExample {1,3,5,7}\n";
    PMTree tree2({'1', '3', '5', '7'});
    auto p2 = getAllPerms(tree2);
    for (int i = 0; i < 8 && i < static_cast<int>(p2.size()); ++i) {
        std::cout << "  " << (i + 1) << ": ";
        printPerm(p2[i]);
    }

    std::cout << "\nExperiment\n";
    std::mt19937_64 rng(42);
    std::printf("%-4s %-16s %-16s %-16s\n",
                "n", "getAllPerms(us)", "getPerm1(us)", "getPerm2(us)");

    for (int n : {2, 3, 4, 5, 6, 7, 8, 9}) {
        auto alpha = makeAlphabet(n);
        PMTree t(alpha);

        int64_t fact = 1;
        for (int i = 1; i <= n; ++i) {
            fact *= i;
        }

        std::uniform_int_distribution<int64_t> dist(1, fact);
        int rn = static_cast<int>(dist(rng));

        auto t0 = std::chrono::high_resolution_clock::now();
        volatile size_t d1 = getAllPerms(t).size();
        auto t1 = std::chrono::high_resolution_clock::now();
        double ua =
            std::chrono::duration<double, std::micro>(t1 - t0).count();

        t0 = std::chrono::high_resolution_clock::now();
        volatile size_t d2 = getPerm1(t, rn).size();
        t1 = std::chrono::high_resolution_clock::now();
        double up1 =
            std::chrono::duration<double, std::micro>(t1 - t0).count();

        t0 = std::chrono::high_resolution_clock::now();
        volatile size_t d3 = getPerm2(t, rn).size();
        t1 = std::chrono::high_resolution_clock::now();
        double up2 =
            std::chrono::duration<double, std::micro>(t1 - t0).count();

        (void)d1;
        (void)d2;
        (void)d3;

        std::printf("%-4d %-16.2f %-16.2f %-16.2f\n", n, ua, up1, up2);
    }

    return 0;
}
