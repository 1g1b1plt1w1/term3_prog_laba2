#include <iostream>
#include "tree.h"
#include <map>
#include <sstream>
using namespace std;

Tree Tree_create() {
    Tree t;
    t.root = nullptr;
    return t;
}

int Tree_get_height(TreeNode* node) {
    if (!node){
        return 0;
    }
    return node->height;
}

void Tree_update_height(TreeNode* node) {
    if (node) {
        int lh = Tree_get_height(node->left);
        int rh = Tree_get_height(node->right);
        node->height = 1 + ((lh > rh) ? lh : rh);
    }
}

int get_balance(TreeNode* node) {
    if (!node) return 0;
    return Tree_get_height(node->left) - Tree_get_height(node->right);
}

TreeNode* Tree_left_rotate(TreeNode* node) {
    TreeNode* node_right = node->right;
    TreeNode* node_right_left = node_right->left;

    node_right->left = node;
    node->right = node_right_left;

    Tree_update_height(node);
    Tree_update_height(node_right);
    return node_right;
}

TreeNode* Tree_right_rotate(TreeNode* node) {
    TreeNode* node_left = node->left;
    TreeNode* node_left_right = node_left->right;

    node_left->right = node;
    node->left = node_left_right;

    Tree_update_height(node);
    Tree_update_height(node_left);
    return node_left;
}

TreeNode* Tree_make_balance(TreeNode* node) {
    int balance = get_balance(node);

    
    if (balance < -1 && get_balance(node->right) <= 0)
        return Tree_left_rotate(node);

    
    if (balance > 1 && get_balance(node->left) >= 0)
        return Tree_right_rotate(node);

    
    if (balance < -1 && get_balance(node->right) > 0) {
        node->right = Tree_right_rotate(node->right);
        return Tree_left_rotate(node);
    }

    
    if (balance > 1 && get_balance(node->left) < 0) {
        node->left = Tree_left_rotate(node->left);
        return Tree_right_rotate(node);
    }

    return node;
}

TreeNode* Tree_insert(TreeNode* node, int data) {
    if (!node) {
        TreeNode* new_node = new TreeNode;
        new_node->data = data;
        new_node->height = 1;
        new_node->left = new_node->right = nullptr;
        return new_node;
    }

    if (data > node->data)
        node->right = Tree_insert(node->right, data);
    else if (data < node->data)
        node->left = Tree_insert(node->left, data);
    else
        return node;

    Tree_update_height(node);
    node = Tree_make_balance(node);
    return node;
}

TreeNode* find_max(TreeNode* node) {
    while (node && node->right) {
        node = node->right;
    }
    return node;
}


TreeNode* Tree_delete(TreeNode* node, int data) {
    if (!node) return nullptr;

    if (data < node->data) {
        node->left = Tree_delete(node->left, data);
    } else if (data > node->data) {
        node->right = Tree_delete(node->right, data);
    } else {
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        } else if (!node->left) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }

        TreeNode* temp = find_max(node->left);
        node->data = temp->data;
        node->left = Tree_delete(node->left, temp->data);
    }

    Tree_update_height(node);

    node = Tree_make_balance(node);

    return node;
}

string Tree_read_node(TreeNode* node) {
    stringstream ss;
    ss << " ";
    if (!node){
        ss << " ";
        return "";
    }
    ss << Tree_read_node(node->left);
    ss << node->data << " ";
    ss << Tree_read_node(node->right);

    return ss.str();
}

string Tree_read(const Tree& tree) {
    if (!tree.root) return "";
    return Tree_read_node(tree.root);
}

bool Tree_find(TreeNode* node, int data) {
    if (node->data == data) {
        return 1;
    }

    if (data > node->data)
        Tree_find(node->right, data);
    else if (data < node->data)
        Tree_find(node->left, data);
    return 0;
}