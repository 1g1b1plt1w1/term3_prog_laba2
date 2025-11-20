#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "tree.h"
#include "task5.h"
using namespace std;
bool check_avl(TreeNode* node) {
    if (!node) return true;

    int bal = get_balance(node);

    if (bal < -1 || bal > 1)
        return false;

    return check_avl(node->left) && check_avl(node->right);
}
