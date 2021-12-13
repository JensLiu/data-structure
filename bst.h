//
// Created by Jens on 18.11.2021.
//

#ifndef BINARY_TREE_LAB_BST_H
#define BINARY_TREE_LAB_BST_H

#include "binary_tree.h"

template <typename T>
class BST : public BinaryTree<T> {

private:
    BSTNode<T>* _find(BSTNode<T>* node, T key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key > node->key) {
            return _find(node->right, key);
        } else if (key < node->key) {
            return _find(node->left, key);
        } else {
            return node;
        }
    }

    BSTNode<T>* _insert(BSTNode<T>*& curNode, T key) {
        if (key > curNode->key) {
            if (curNode->right == nullptr) {
                BSTNode<T>* node = new BSTNode<T>(key);
                curNode->right = node;
                node->parent = curNode;
                return node;
            } else {
                return _insert(curNode->right, key);
            }
        } else if (key < curNode->key) {
            if (curNode->left == nullptr) {
                BSTNode<T>* node = new BSTNode<T>(key);
                curNode->left = node;
                node->parent = curNode;
                return node;
            } else {
                return _insert(curNode->left, key);
            }
        } else {
            return nullptr;
        }

    }

    BSTNode<T>* _findMin(BSTNode<T>* node) {
        BSTNode<T>* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    BSTNode<T>* _findMax(BSTNode<T>* node) {
        BSTNode<T>* current = node;
        while (current->right != nullptr) {
            current = current->right;
        }
    }

    /**
     * this function returns the next larger node
     * @param node
     * @return
     */
    BSTNode<T>* _findNextLarger(BSTNode<T>* node) {
        if (node == nullptr) return nullptr;

        // if it has right child
        if (node->right != nullptr) {
            return _findMin(node->right);
        } else {
            BSTNode<T> *current = node;

            /* cannot find the next larger:
             *  example:
             *      7
             *     / \
             *    1  nil
             *
             * NEED TO SHOW that this situation only occur when:
             *      root            root
             *      / \             / \
             *   left  nil       nil  nil
             *
             *  proof:
             *
             *  we first prove that the node has no right child:
             *      if it has right child, the flow of control will return before entering the clause
             *  then we prove that the node is the root:
             *      if its parent is null, then it is the root
             *
             */
            if (current->parent == nullptr) { // this situation is found during testing
                return nullptr;
            }

            while (current == current->parent->right) {
                current = current->parent;
            }
            return current->parent;
        }
    }

    BSTNode<T>* _findNextSmaller(BSTNode<T>* node) {
        if (node == nullptr) return nullptr;

        if (node->left != nullptr) {
            return node->left;
        } else {
            BSTNode<T> *current = node;
            while (current != current->parent->left) {
                current = current->parent;
            }
            return current->parent;
        }
    }

    BSTNode<T>* _deleteNode(BSTNode<T>* node) {

        // if node has either one or non child
        if (node->left == nullptr || node->right == nullptr) {

            // if node is the left child of its parent
            if (node == node->parent->left) {
                if (node->left != nullptr) {
                    node->parent->left = node->left;
                } else {
                    node->parent->left = node->right;
                }

                if (node->parent->left != nullptr) {
                    node->parent->left->parent = node->parent;
                }
            } else if (node == node->parent->right) { // if node is the right child of its parent

                if (node->left != nullptr) {
                    node->parent->right = node->left;
                } else {
                    node->parent->right = node->right;
                }
                if (node->parent->right != nullptr) {
                    node->parent->right->parent = node->parent;
                }
            }
            return node;
        } else {
            /*
             * if this node is the right child of its parent
             * then:  node > parent
             *
             * to preserve BST property, need to find its successor:
             *      that is: greater than the current node but smaller than any other nodes in the right subtree
             *      can be found on: the left most node in the right subtree
             *
             *
             *  NEED TO SHOW that its successor has only one subtree or is a leaf node:
             *  proof:
             *
             *      by way of contradiction:
             *          if the node has left and right subtree
             *          then nodes in the left subtree are smaller than this node
             *          it is not the successor, contradictory (x)
             *      we conclude that the successor has either no subtrees or only the right subtree
             *
             *      END OF PROOF
             *
             *  so its successor satisfies the first case, we can call deletion on it
             *
             *  similarly, we can prove that:
             *      the predecessor can be found in the right most node in the left tree
             *
             *  without the loss of generality, we take the node that is the right child of its parent:
             *  NEED TO SHOW that after switching with its successor, the resulting tree preserves BST property
             *  proof:
             *
             *      before switching
             *
             *
             */
            BSTNode<T>* next = node;
            if (node == node->parent->left) {
                next = _findNextSmaller(node);
            } else {
                next = _findNextLarger(node);
            }
            T tmp = node->key;
            node->key = next->key;
            next->key = tmp;
            return _deleteNode(next);
        }
    }

    void _transplant(BSTNode<T>* toNode, BSTNode<T>* fromNode) {
        if (toNode->parent == nullptr) {
            this->root = fromNode;
        } else {
            if (toNode == toNode->parent->left) {
                toNode->parent->left = fromNode;
            } else {
                toNode->parent->right = toNode;
            }
        }
        if (fromNode != nullptr) {
            fromNode->parent = toNode->parent;
        }
    }

    BSTNode<T>* _deleteNode_iterative(BSTNode<T>* node) {
        if (node->right == nullptr) {
            _transplant(node, node->left);
        } else if (node->left == nullptr) {
            _transplant(node, node->right);
        } else {
            BSTNode<T>* next = _findMin(node->right);
            if (next->parent != node) {
                _transplant(next, next->right);
                next->right = node->right;
                if (next->right != nullptr)
                    next->right->parent = next;
            }
            _transplant(node, next);
            next->left = node->left;
            if (next->left != nullptr)
                next->left->parent = next;
        }
        return node;
    }

public:

     BSTNode<T>* insert(T key) {
        if (this->root == nullptr) {
            this->root = new BSTNode<T>(key);
        }
        BSTNode<T>* node = _insert(this->root, key);
        return node;
    }

     BSTNode<T>* deleteNode(T key) {
        if (this->root == nullptr) {
            return nullptr;
        }
        BSTNode<T>* node = _find(this->root, key);
        if (node == this->root) {
            BSTNode<T>* next = _findNextLarger(this->root);

            /*
             *  cannot find the next larger:
             *
             *  We already proved that it is only true in the following two cases:
             *  (proof is in the comments of _findNextLarger function)
             *      root            root
             *      / \             / \
             *   left  nil       nil  nil
             *
             *
             *  Example:
             *      7           1
             *     / \         / \
             *    1  nil    nil  nil
             */
            if (next == nullptr) { // this situation is found during testing
                this->root = node->left;
                if (this->root != nullptr) {
                    this->root->parent = nullptr;
                }
                return node;
            }

            T tmp = this->root->key;
            this->root->key = next->key;
            next->key = tmp;

            return _deleteNode(next);
        } else {
            return _deleteNode(node);
        }
    }

    BSTNode<T>* deleteNode_iterative(T key) {
        if (this->root == nullptr) {
            return nullptr;
        }
        BSTNode<T>* node = _find(this->root, key);
        if (node == nullptr) {
            return nullptr;
        }
        return _deleteNode_iterative(node);
    }

    bool find(T key) {
        if (_find(this->root, key) == nullptr) {
            return false;
        } else {
            return true;
        }
    }

    virtual void leftRotate(BSTNode<T>* node) {
        BSTNode<T>* x = node;
        BSTNode<T>* y = node->right;
        BSTNode<T>* p = x->parent;
        x->right = y->left;
        if (x->right != nullptr) {
            x->right->parent = x;
        }
        y->left = x;
        y->left->parent = y;
        y->parent = p;
        if (p == nullptr) {
            this->root = y;
        } else if (x == p->left) {
            p->left = y;
        } else if (x == p->right) {
            p->right = y;
        }
        updateHeight(x);
        updateHeight(y);
    }

    virtual void rightRotate(BSTNode<T>* node) {
        BSTNode<T>* x = node;
        BSTNode<T>* y = node->left;
        BSTNode<T>* p = x->parent;
        x->left = y->right;
        if (x->left != nullptr) {
            x->left->parent = x;
        }
        y->right = x;
        y->right->parent = y;
        y->parent = p;
        if (p == nullptr) {
            this->root = y;
        } else if (x == p->left) {
            p->left = y;
        } else if (x == p->right) {
            p->right = y;
        }
        updateHeight(x);
        updateHeight(y);
    }

};
#endif //BINARY_TREE_LAB_BST_H
