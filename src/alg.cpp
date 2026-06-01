// Copyright 2022 NNTU-CS
#include <algorithm>
#include <vector>
#include  "tree.h"
PMTree::PMTree(const std::vector<char>& in) {
    std::vector<char> sorted_in = in;
    std::sort(sorted_in.begin(), sorted_in.end());
    for (char c : sorted_in) {
        PMNode* node = new PMNode(c);
        std::vector<char> remaining;
        for (char x : sorted_in) if (x != c) remaining.push_back(x);
        build(node, remaining);
        roots.push_back(node);
    }
}

PMTree::~PMTree() { for (auto* r : roots) delete r; }

void PMTree::build(PMNode* node, std::vector<char> remaining) {
    if (remaining.empty()) return;
    for (char c : remaining) {
        PMNode* child = new PMNode(c);
        std::vector<char> next;
        for (char x : remaining) if (x != c) next.push_back(x);
        build(child, next);
        node->children.push_back(child);
    }
}

static void dfs(PMNode* node, std::vector<char>& cur,
                std::vector<std::vector<char>>& res) {
    cur.push_back(node->value);
    if (node->children.empty()) { res.push_back(cur); }
    else { for (PMNode* ch : node->children) dfs(ch, cur, res); }
    cur.pop_back();
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> res;
    std::vector<char> cur;
    for (PMNode* r : tree.roots) dfs(r, cur, res);
    return res;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    if (num <= 0) return {};
    auto all = getAllPerms(tree);
    if (num > (int)all.size()) return {};
    return all[num - 1];
}

static long long factorial(int n) {
    long long f = 1;
    for (int i = 2; i <= n; ++i) f *= i;
    return f;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    if (num <= 0) return {};
    int n = (int)tree.roots.size();
    if ((long long)num > factorial(n)) return {};
    std::vector<char> res;
    long long idx = num - 1;
    const std::vector<PMNode*>* level = &tree.roots;
    for (int depth = n; depth > 0; --depth) {
        long long pps = factorial(depth - 1);
        int ci = (int)(idx / pps);
        idx %= pps;
        if (ci >= (int)level->size()) return {};
        PMNode* chosen = (*level)[ci];
        res.push_back(chosen->value);
        level = &chosen->children;
    }
    return res;
}
