#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    int height;
    TreeNode* left;
    TreeNode* right;
};

struct Tree {
    TreeNode* root;
};

Tree Tree_create();
int Tree_get_height(TreeNode* node);
void Tree_update_height(TreeNode* node);
int get_balance(TreeNode* node);
TreeNode* Tree_left_rotate(TreeNode* node);
TreeNode* Tree_right_rotate(TreeNode* node);
TreeNode* Tree_make_balance(TreeNode* node);
TreeNode* Tree_insert(TreeNode* node, int data);
TreeNode* Tree_delete(TreeNode* node, int data);
TreeNode* find_max(TreeNode* node);
string Tree_read(const Tree& node);
bool is_member(const Tree& node, int find_data);
void Tree_print(const Tree& node);
#endif
