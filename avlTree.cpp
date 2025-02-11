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
AVLTreeNode* AVLTree::remove(int value, AVLTreeNode* node){
    if(node == nullptr){
        return nullptr;
    }
    if(value < node->value){
        return remove(value, node->left);
    }
    else if(value > node->value){
        return remove(value, node->right);
    }
    else if(node->left != nullptr && node->right!= nullptr){
        node->value = findMin(node->right)->value;
        node->right = remove(node->value, node->right);

    }
        else{
            // found match, single child or no child
            AVLTreeNode* oldNode = node;
            node = (node->left != nullptr) ? node->left: node->right;
            delete oldNode;

        }
    node = balance(node);
    return node;
}

int AVLTree::height(AVLTreeNode* node){
    return node == nullptr ? -1: node->height;
}
AVLTreeNode* AVLTree::balance(AVLTreeNode* node){
    if(node == nullptr){
        return nullptr;
    }
    if(height(node->left) - height(node->right) > 1){
        // LL imbalance case 
        if(height(node->left->left ) >= height(node->left->right)){
            node = rightRotate(node);
        }
        // LR imbalance case 
        else{
            node = leftRightDoubleRotate(node);
        }
    }
    // RR imbalance case 
    else if (height(node->right) - height(node->left) > 1){
        if (height(node->right->right) >= height(node->right->left)){
            node = leftRotate(node);
        }
        // RL imbalance case 
        else{
            node = rightLeftDoubleRotate(node);
        }
    }
    updateHeight(node);
    return node;
}