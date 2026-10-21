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

void run_task5() {
    cout << "Введите последовательность чисел, оканчивающуюся нулем: ";
    Tree t = Tree_create();
    int val = 0;
    while (cin >> val && val != 0) {
        t.root = Tree_insert(t.root, val);
    }
    Tree_print(t);
}
