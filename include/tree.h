// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <algorithm>

struct PMNode {
    char value;
    std::vector<PMNode*> children;
    explicit PMNode(char v) : value(v) {}
    ~PMNode() { for (auto* c : children) delete c; }
};

class PMTree {
public:
    std::vector<PMNode*> roots;
    explicit PMTree(const std::vector<char>& in);
    ~PMTree();
private:
    void build(PMNode* node, std::vector<char> remaining);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
