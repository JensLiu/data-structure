//
// Created by Jens on 18.11.2021.
//

#ifndef BINARY_TREE_LAB_AVL_TREE_H
#define BINARY_TREE_LAB_AVL_TREE_H

#include "bst.h"

template <typename T>
class AVL: public BST<T> {
public:
    void rebalance(BSTNode<T>* node) {
        while (node != nullptr) {
            updateHeight(node);
            if (nodeHeight(node->left) >= 2 + nodeHeight(node->right)) {
                // left heavy
                if (nodeHeight(node->left->left) >= nodeHeight(node->left->right)) {
                    // doubly left heavy
                    this->rightRotate(node);
                } else {
                    this->leftRotate(node->left);
                    this->rightRotate(node);
                }
            } else if (nodeHeight(node->right) >= 2 + nodeHeight(node->left)) {
                if (nodeHeight(node->right->right) >= nodeHeight(node->right->left)) {
                    this->leftRotate(node);
                } else {
                    this->rightRotate(node->right);
                    this->leftRotate(node);
                }
            }
            node = node->parent;
        }
    }

    BSTNode<T>* insert(T key) {
        // inset the key using BST's method
        BSTNode<T>* node = BST<T>::insert(key);
        // the key inserted may violate the avl property
        // do rebalanced
        rebalance(node);
        return node;
    }

    BSTNode<T>* deleteNode(T key) {
        // delete the node using BST's method
        BSTNode<T>* node = BST<T>::deleteNode(key);
        // the removing of key may violate the avl property
        // rebalance
        rebalance(node);
        return node;
    }

    BSTNode<T>* deleteNode_iterative(T key) {
        BSTNode<T>* node = BST<T>::deleteNode_iterative(key);
        return node;
    }

};
#endif //BINARY_TREE_LAB_AVL_TREE_H
