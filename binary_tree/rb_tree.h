//
// Created by Jens on 25.11.2021.
//

#ifndef BINARY_TREE_LAB_RB_TREE_H
#define BINARY_TREE_LAB_RB_TREE_H
#include "bst.h"
template <typename T>
class RBTree {
    BSTNode<T> *nil;
    BSTNode<T>* root;
public:
    RBTree() {
        this->nil = new BSTNode<T>;
        this->nil->setNil();
        this->root = nil;
    }
    ~RBTree() {

    }

private:
    void _deleteNode(BSTNode<T>* node) {
        if (node == nil) {
            return;
        }
        if (node->left == nil && node->right == nil) {
            delete node;
        }
        _deleteNode(node->left);
        _deleteNode(node->right);
    }
    void _preOrderWalk(BSTNode<T>* node) {
        if (node == nil) {
            return;
        }
        std::cout << node->key << " ";
        _preOrderWalk(node->left);
        _preOrderWalk(node->right);
    }
    void leftRotate(BSTNode<T>* node) {
        BSTNode<T>* x = node;
        BSTNode<T>* y = node->right;
        BSTNode<T>* p = x->parent;
        x->right = y->left;
        if (x->right != nil) {
            x->right->parent = x;
        }
        y->left = x;
        y->left->parent = y;
        y->parent = p;
        if (p == nil) {
            this->root = y;
        } else if (x == p->left) {
            p->left = y;
        } else if (x == p->right) {
            p->right = y;
        }
        updateHeight(x);
        updateHeight(y);
    }
    void rightRotate(BSTNode<T>* node) {
        BSTNode<T>* x = node;
        BSTNode<T>* y = node->left;
        BSTNode<T>* p = x->parent;
        x->left = y->right;
        if (x->left != nil) {
            x->left->parent = x;
        }
        y->right = x;
        y->right->parent = y;
        y->parent = p;
        if (p == nil) {
            this->root = y;
        } else if (x == p->left) {
            p->left = y;
        } else if (x == p->right) {
            p->right = y;
        }
        updateHeight(x);
        updateHeight(y);
    }
    void _BRInsertFixup(BSTNode<T> *node) {
        BSTNode<T> *p = node;
        while (p->parent != this->root && p->parent->nodeColour == BSTNode<T>::RED) {
            if (node->parent == node->parent->parent->left) {
                BSTNode<T> *uncle = p->parent->parent->right;
                if (uncle->nodeColour == BSTNode<T>::RED) {
                    p->parent->parent->colourRed();
                    p->parent->colourBlack();
                    uncle->colourBlack();
                    p = p->parent->parent;
                } else {
                    if (p == p->parent->right) {
                        leftRotate(p->parent);
                        p = p->right;
                    }
                    rightRotate(p->parent->parent);
                    p->parent->colourBlack();
                    p->parent->right->colourRed();

                }
            } else {
                BSTNode<T> *uncle = p->parent->parent->left;
                if (uncle->nodeColour == BSTNode<T>::RED) {
                    p->parent->parent->colourRed();
                    p->parent->colourBlack();
                    uncle->colourBlack();
                    p = p->parent->parent;
                } else {
                    if (p == p->parent->left) {
                        rightRotate(p);
                        p = p->left;
                    }
                    leftRotate(p->parent->parent);
                    p->parent->colourBlack();
                    p->parent->left->colourRed();
                }
            }
        }
        this->root->colourBlack();
    }

    void _RBInsert(BSTNode<T> *node) {
        BSTNode<T>* x = this->root;
        BSTNode<T>* y = this->nil; // y is the parent of x
        while (x != nil) {
            y = x;
            if (node->key > x->key) {
                x = x->right;
            } else if (node->key < x->key) {
                x = x->left;
            } else {
                return;
            }
        }
        node->parent = y;
        if (y == nil) { // if it is an empty tree, insert node at root
            this->root = node;
        } else if (node->key > y->key) {
            y->right = node;
        } else if (node->key < y->key) {
            y->left = node;
        } else {
            return;
        }
        node->left = nil;
        node->right = nil;
        _BRInsertFixup(node);

    }

    void RBDeleteFixup(BSTNode<T>* node) {
        if (node == node->parent->left) {
//            if (node->parent->right->nodeColour == BSTNode<T>::RED) {
//                rightRotate(node->parent->right)
//            }

        }
    }

public:
    void preOrderWalk() {
        _preOrderWalk(this->root);
    }

    BSTNode<T> *insert(T key) {
        BSTNode<T> *node = new BSTNode<T>(key);
        _RBInsert(node);
        return nullptr;
    }

    void printTree(int wide) {
        if (this->root == nullptr) {
            std::cout << "empty tree";
            return;
        }

        std::vector<BSTNode<T>*> completeBST;
        std::queue<BSTNode<T>*> level_queue;

        level_queue.push(root);

        // count depth starting from 1
        int depth = nodeHeight(root) + 1;

        // create an internal nil
        // insight: nil->left = nil, nil->right = nil
        BSTNode<T>* pseudoNil = new BSTNode<T>; pseudoNil->setInternalNil();

        // converting to a complete binary tree

        unsigned nodeCount = pow(2, root->height + 1) - 1;
        for (unsigned int i = 0; i < nodeCount; i++) {
            if (i >= UINT32_MAX - 1) {
                std::cout << "too many nodes" << std::endl;
                return;
            }
            BSTNode<T>* node = level_queue.front(); level_queue.pop();
            if (node->left != this->nil) {
                level_queue.push(node->left);
            } else {
                level_queue.push(pseudoNil);
            }
            if (node->right != this->nil) {
                level_queue.push(node->right);
            } else {
                level_queue.push(pseudoNil);
            }
            completeBST.push_back(node);
        }

        // how many spaces are needed
        std::list<int> space_list;
        space_list.push_front(1);
        for (int i = 0; i < depth; i++) {
            space_list.push_front(space_list.front() * 2 + 1);
        }
        space_list.push_front( 0);
        std::list<int>::iterator it = space_list.begin();
        // print tree
        for (int i = 1; i <= depth; i++) {
            int midSpace = *it;
            int beginSpace = *(++it);
            for (int j = 0; j < beginSpace; j++) {
                std::cout << std::setw(wide) << " ";
            }
            for (int k = pow(2, i - 1) - 1; k < pow(2, i) - 1; k++) {
                if (!completeBST[k]->isNil()) {
                    std::cout << std::setw(wide) << completeBST[k]->key;
                } else {
                    std::cout << std::setw(wide) << " ";
                }
                for (int j = 0; j < midSpace; j++) {
                    std::cout << std::setw(wide) << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};
#endif //BINARY_TREE_LAB_RB_TREE_H
