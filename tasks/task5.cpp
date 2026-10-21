#include <iostream>
#include <vector>
#include "tree.h"
#include "task5.h"

using namespace std;

void print_snake(Tree t) {
    if (t.root == nullptr) {
        return;
    }

    vector<TreeNode*> q;
    q.push_back(t.root);

    int head = 0;
    bool reverse_order = false;
    bool first_elem = true;

    while (head < (int)q.size()) {
        int level_start = head;
        int level_end = q.size();

        if (!reverse_order) {
            for (int i = level_start; i < level_end; ++i) {
                if (!first_elem) cout << " - ";
                cout << q[i]->data;
                first_elem = false;
            }
        } else {
            for (int i = level_end - 1; i >= level_start; --i) {
                if (!first_elem) cout << " - ";
                cout << q[i]->data;
                first_elem = false;
            }
        }

        for (int i = level_start; i < level_end; ++i) {
            if (q[i]->left != nullptr) {
                q.push_back(q[i]->left);
            }
            if (q[i]->right != nullptr) {
                q.push_back(q[i]->right);
            }
        }

        head = level_end;
        reverse_order = !reverse_order;
    }

    cout << endl;
}

void run_task5() {
    cout << "Введите последовательность чисел, оканчивающуюся нулем: ";
    Tree t = Tree_create();
    int val = 0;
    while (cin >> val && val != 0) {
        t.root = Tree_insert(t.root, val);
    }
    print_snake(t);
}