#include "avlTree.hpp"

bool AVLTree::contains(int value, AVLTreeNode* node){
    if (node == nullptr){
        return false;
    }
    if(node->value == value){
        return true;
    }
    if(value < node->value){
        return contains(value, node->left);
    }
    return contains(value, node->right);
}

AVLTreeNode* AVLTree::insert(int value, AVLTreeNode* node){
    if (node == nullptr){
        node = new AVLTreeNode(value);
    }
    if (value < node->value){
        node->left = insert(value, node->left);
    }
    else if(value > node->value){
        node->right = insert(value, node->right);
    }
    node = balance(node);
    return node;
}