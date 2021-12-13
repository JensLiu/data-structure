//
// Created by Jens on 18.11.2021.
//

#ifndef BINARY_TREE_LAB_BINARY_TREE_H
#define BINARY_TREE_LAB_BINARY_TREE_H

#include "bst_node.h"
#include <iostream>
#include <iomanip>
// the use of standard template library is only for
// breath first search, iterative implementation of tree traversal
// and printing tree in the console
#include <unordered_map>
#include <stack>
#include <list>
#include <queue>

template <typename T>
class BinaryTree {

protected:
    BSTNode<T>* root;

public:
    BinaryTree() {
        this->root = nullptr;
    }

private:
    /**
     * This function update the height of a given node
     * (We define that the height of a leaf node is 0)
     * @param node node the height of which to be updated
     * @return updated height
     */
    int _updateNodeHeight(BSTNode<T>* node) {
        /*
         * by definition, the height of a node is the longest simple path from current node to the descending leaf node
         * hence the height of a leaf node is 0
         *
         * thus the height of a leaf node = max(h_nil, h_nil) + 1
         * thus max(h_nil, h_nil) = h_nil = -1
         */
        if (node == nullptr) {
            return -1;
        } else {
            node->height =
                    std::max(_updateNodeHeight(node->left), _updateNodeHeight(node->right)) + 1;
            return node->height;
        }
    }

    /**
     * this is a intermediate function that creates tree/subtree
     * with a pre-order and an in-order traversal sequence
     *
     * @param preArr start position of an array of the pre-order traversal sequence of the tree
     * @param inArr start position of an array of the in-order traversal sequence of the tree
     * @param total total number of nodes of the tree
     * @return the root node generated for the tree
     */
    BSTNode<T>* _preAndInWalkInsert(T* preArr, T* inArr, const int& total) {
        /*
         *
         *
         * property for pre-order sequence:
         *      the root node of the tree can always be found on the position 0 of the sequence
         * property for in-order sequence:
         *      the left and right subtree of the root are distributed on both sides of the root node
         *
         *  =>  Hence, we can always find a tree root and two subtrees with these two sequence recursively
         *
         *      proof:
         *      need to show: for any correct pre-order and in-order walk sequence,
         *      we can always construct a binary tree
         *
         *      use induction:
         *          BASE CASE: an empty tree (total = 0)
         *              => return nil as the subtree root
         *
         *          MAINTENANCE:
         *              *preArr is the value of the root of the tree to be constructed
         *              we can always find the root in the in-order sequence, and store the position as *rootPos
         *
         *              create a tree root with value being the element in the first position of preArr
         *
         *              hence, in the in-order sequence:
         *                  [inArr, rootPos-1] is the left subtree, [rootPos+1, inArr+(total-1)] is the right subtree
         *
         *                  length of the left subtree: l_left = (rootPos - inArr)
         *                  length of the right subtree: l_right = total - (l_left + 1) = total - (rootPos - inArr + 1)
         *
         *               similarly, in the pre-order sequence:
         *                  [preArr+1, preArr+l_left] is the left subtree, [preArr+(l_left+1), preArr+(total-1)] is the right subtree
         *
         *
         *              we ASSUME THE HYPOTHESIS HOLD FOR INDUCTIVE PURPOSE,
         *              that the left subtree and the right subtree are already constructed
         *              then assign them to root.left, root.right respectively, then root is a new binary tree
         *
         *          END OF PROOF
         *
         *
         */
        if (total > 0) {
            // create current node and set it's value
            BSTNode<T>* curNode = new BSTNode<T>;
            curNode->key = *preArr;

            // find the root in the in-order sequence
            T* trav = inArr;

            // count the length of the right subtree as it finds the root in the in-order sequence
            int leftLength = 0;

            while (*trav != *preArr && trav != inArr + total) {
                // stop only when *trav == *preArr (the value equal to the root found in pre-order sequence)
                // or (if it doesn't found the root shouldn't happen) out of bound of the in-order sequence
                trav++;
                leftLength++;
            }
            // upon exit, the rightLength is the length also includes an extra length of the root node
            int rightLength = total - leftLength - 1;

            // create left subtree
            curNode->left = _preAndInWalkInsert(preArr + 1, inArr, leftLength);
            if (curNode->left != nullptr) {
                // set parent if not null
                curNode->left->parent = curNode;
            }

            // create right subtree
            curNode->right = _preAndInWalkInsert(preArr + leftLength + 1, inArr + leftLength + 1, rightLength);
            if (curNode->right != nullptr) {
                // set parent if not null
                curNode->right->parent = curNode;
            }

            // update the height of current node
            _updateNodeHeight(curNode);
            return curNode;

        } else {
            return nullptr;
        }
    }

    BSTNode<T>* _postAndInWalkInsert(T* postArr, T* inArr, const int& total) {
        /*
         *
         *
         *  Similarly to the proof above, notice that:
         *
         *      postArr+(total-1) is the value of the root node
         *
         *      we can find the left length l_left by finding the position containing the same value as the root in the in-order sequence
         *      the right length l_right = total - (l_left + 1)
         *
         *      hence,
         *      in post-order sequence,
         *          [postArr, postArr+(l_left-1)] is the left subtree,
         *          [postArr+(l_left-1)+1+1, postArr+(total-1)-1] which simplifies to [postArr+l_left+1, postArr+total-2] is the right subtree
         *      in the in-order sequence,
         *          [inArr, inArr+(l_left-1)] is the left subtree
         *          [inArr+l_left, inArr+(total-1] is the right subtree
         *
         *
         */
        if (total > 0) {
            T* rootPtr = postArr + total - 1;

            BSTNode<T>* curNode = new BSTNode<T>;
            curNode->key = *rootPtr;

            T* trav = inArr;
            int leftLength = 0;
            while (*trav != *(rootPtr) && trav != postArr + total) {
                trav++;
                leftLength++;
            }
            int rightLength = total - leftLength - 1;

            curNode->left = _postAndInWalkInsert(postArr, inArr, leftLength);
            if (curNode->left != nullptr) {
                curNode->left->parent = curNode;
            }
            curNode->right = _postAndInWalkInsert(postArr + leftLength, inArr + leftLength + 1, rightLength);
            if (curNode->right != nullptr) {
                curNode->right->parent = curNode;
            }
            _updateNodeHeight(curNode);
            return curNode;
        } else {
            return nullptr;
        }
    }

    void _preOrderWalk(BSTNode<T>* node, void (*displayformat)(T data) = nullptr) {
        if (node != nullptr) {
            if (displayformat == nullptr) {
                std::cout << node->key << " ";
            } else {
                displayformat(node->key);
            }
            _preOrderWalk(node->left);
            _preOrderWalk(node->right);
        } else {
            std::cout << "# ";
        }
    }

    void _inOrderWalk(BSTNode<T>* node, void (*displayformat)(T data) = nullptr) {
        if (node != nullptr) {
            _inOrderWalk(node->left);
            if (displayformat == nullptr) {
                std::cout << node->key << " ";
            } else {
                displayformat(node->key);
            }
            _inOrderWalk(node->right);
        } else {
            std::cout << "# ";
        }
    }

    void _postOrderWalk(BSTNode<T>* node, void (*displayformat)(T data) = nullptr) {
        if (node != nullptr) {
            _postOrderWalk(node->left);
            _postOrderWalk(node->right);
            if (displayformat == nullptr) {
                std::cout << node->key << " ";
            } else {
                displayformat(node->key);
            }
        } else {
            std::cout << "# ";
        }
    }

    BSTNode<T>* _preOrderCopy(BSTNode<T>* fromNode) {
        if (fromNode == nullptr) {
            return nullptr;
        }
        BSTNode<T>* newNode = new BSTNode<T>(fromNode->key);
        newNode->left = _preOrderCopy(fromNode->left);
        if (newNode->left != nullptr)
            newNode->left->parent = newNode;
        newNode->right = _preOrderCopy(fromNode->right);
        if (newNode->right != nullptr)
            newNode->right->parent = newNode;
        return newNode;
    }

    /**
     * this is a intermediate function that deletes a node and its subtrees were there any
     * @param node node to be deleted
     */
    void _deleteNode(BSTNode<T>* node) {
        // if the node is a null pointer, no need to delete
        if (node == nullptr) {
            return;
        }

        // if the node is a leaf node, delete it
        if (node->left == nullptr && node->right == nullptr) {
            // if the node has a parent, then set the pointer from the parent to it to null
            if (node->parent != nullptr && node == node->parent->left) {
                node->parent->left = nullptr;
            }
            if (node->parent != nullptr && node == node->parent->right) {
                node->parent->right = nullptr;
            }
            delete node;
        } else {
            // if the node is not a leaf node, delete its subtrees then delete itself
            _deleteNode(node->left);
            _deleteNode(node->right);
            delete node;
        }
    }

    void _nodesOnDepth(const int& requiredDepth, BSTNode<T>* node, int depth, int& count) {
        if (node == nullptr) {
            return;
        }
        if (depth == requiredDepth) {
            count++;
        }
        _nodesOnDepth(requiredDepth, node->left, depth+1, count);
        _nodesOnDepth(requiredDepth, node->right, depth+1, count);
    }

    bool _holdsBSTProperty(BSTNode<T>* node) {
        if (node == nullptr) {
            return true;
        } else if (node->left != nullptr && node->left->key >= node->key || node->right != nullptr && node->right->key <= node->key) {
            return false;
        } else {
            return _holdsBSTProperty(node->left) && _holdsBSTProperty(node->right);
        }
    }

public:
    /**
     * this function gives the depth of current node
     * by treating it as if it were in the calling binary tree
     *
     * @param node
     * @return the depth of the node
     */
    int getNodeDepth(BSTNode<T>* node) {
        return root->height - node->height;
    }


    /**
     * this function returns the root node of the current binary tree
     * SHOULD NOT USE THIS because it violates the encapsulation nature of the binary tree class
     * @return the root of the current binary tree
     */
    BSTNode<T>* getRootNode() {
        return root;
    }

    /**
     * the copy constructor that does a deep copy from the given tree to the current tree
     * @param fromTree
     */
    BinaryTree(const BinaryTree<T>& fromTree) {
        this->root = _preOrderCopy(fromTree.root);
    }

    /**
     * destructor that removes all the nodes
     */
    ~BinaryTree() {
        _deleteNode(root);
    }

    /**
     * this function does a deep copy from the given tree to current tree and erases all data from current tree
     * @param fromTree
     */
    void copyFrom(const BinaryTree<T>& fromTree) {
        if (this->root != nullptr) {
            _deleteNode(root);
        }
        root = _preOrderCopy(fromTree.root);
    }

    /**
     * this function prints the level-order walk sequence of the tree to the console
     * @param displayformat a pointer to the function that prints the data of the generic type to the console
     * <p>leave blank to use the default format
     * @example using a lambda function: @code
     *      treeInstance.levelOrderWalk([}(int data){
     *          cout << data << ", ";
     *      });
     */
    void levelOrderWalk(void (*displayformat)(T data) = nullptr) {
        std::queue<BSTNode<T>*> level_queue;
        level_queue.push(root);
        while (!level_queue.empty()) {
            BSTNode<T>* node = level_queue.front(); level_queue.pop();
            if (node->left != nullptr)
                level_queue.push(node->left);
            if (node->right != nullptr)
                level_queue.push(node->right);
            if (displayformat == nullptr) {
                std::cout << node->key << " ";
            } else {
                displayformat(node->key);
            }
        }
    }

    void preOrderWalk_iterative() {
        std::stack<BSTNode<T>*> pre_stack;
        pre_stack.push(root);
        BSTNode<T>* node = pre_stack.top();
        BSTNode<T>* nil = new BSTNode<T>; nil->setTermenalNil();
        while (!pre_stack.empty()) {
            node = pre_stack.top(); pre_stack.pop();

            if (node->isNilNode) {
                std::cout << "# ";
                continue;
            } else {
                std::cout << node->key << " ";
            }

            if (node->right != nullptr) {
                pre_stack.push(node->right);
            } else {
                pre_stack.push(nil);
            }
            if (node->left != nullptr) {
                pre_stack.push(node->left);
            } else {
                pre_stack.push(nil);
            }
        }
    }

    void inOrderWalk_iterative() {
        std::stack<BSTNode<T>*> stack;
        BSTNode<T>* p = this->root;
        stack.push(p);
        while (!stack.empty() || p != nullptr)  {
            while (p != nullptr) {
                stack.push(p);
                p = p->left;
            }
            if (!stack.empty()) {
                p = stack.top();
                std::cout << p->key << " ";
                p = p->right;
                stack.pop();
            }
        }
    }

    void postOrderWalk_iterative() {
        /* use hash table to record status
         * not in hash table: haven't visited
         * in hash table:
         *      value = false: pending
         *      value = true: done visiting both subtrees
         */
        std::unordered_map<BSTNode<T>*, bool> visited;
        std::stack<BSTNode<T>*> stack;
        stack.push(this->root);

        while (!stack.empty()) {
            BSTNode<T>* node = stack.top();

            if (visited.find(node) == visited.end()) { // for new node, push into stack
                if (node->right != nullptr)
                    stack.push(node->right);
                if (node->left != nullptr)
                    stack.push(node->left);
                visited.insert({node, false});
            } else if (visited.at(node) == true) { // for node that have both its children visited, remove and print out
                std::cout << node->key << " ";
                stack.pop();
            }

            if (node->left == nullptr && node->right == nullptr) { // node is a leaf node, then we visited it
                visited.at(node) = true;
                if (node->parent != nullptr && node == node->parent->right) // if the node is the right child
                    /* since we first visit the left child, then right child
                     * when visiting right child, the left child is said to be visited already
                     * so its parent have both of subtrees visited
                     */
                    visited.at(node->parent) = true;
            } else if (node->left != nullptr && visited.find(node->left) != visited.end() ||
                        node->right != nullptr && visited.find(node->right) != visited.end()) {
                visited.at(node) = true;
                if (node->parent != nullptr)
                    visited.at(node->parent) = true;
            }
        }
    }



    /**
     * this function takes a pre-order and an in-order traversal sequence array to build a binary tree
     *
     * @param preArr an array of the pre-order traversal sequence of the tree
     * @param inArr an array of the in-order traversal sequence of the tree
     * @param total total number of nodes of the tree
     */
    void preAndInWalkInsert(T* preArr, T* inArr, int total) {
        this->root = _preAndInWalkInsert(preArr, inArr, total);
        _updateNodeHeight(this->root);
    }

    /**
     * this function takes a post-order and an in-order traversal sequence array to build a binary tree
     *
     * @param postArr an array of the post-order traversal sequence of the tree
     * @param inArr an array of the in-order traversal sequence of the tree
     * @param total total number of nodes of the tree
     */
    void postAndInWalkInsert(T* postArr, T* inArr, int total) {
        this->root = _postAndInWalkInsert(postArr, inArr, total);
        _updateNodeHeight(this->root);
    }

    /**
     * this function prints the pre-order walk sequence of the tree to the console
     * @param displayformat a pointer to the function that prints the data of the generic type to the console
     * <p>leave blank to use the default format
     * @example using a lambda function: @code
     *      treeInstance.preOrderWalk([}(int data){
     *          cout << data << ", ";
     *      });
     */

    void preOrderWalk(void (*displayformat)(T data) = nullptr) {
        _preOrderWalk(this->root, displayformat);
    }

    /**
     * this function prints the in-order walk sequence of the tree to the console
     * @param displayformat a pointer to the function that prints the data of the generic type to the console
     * <p>leave blank to use the default format
     * @example using a lambda function: @code
     *      treeInstance.inOrderWalk([}(int data){
     *          cout << data << ", ";
     *      });
     */
    void inOrderWalk(void (*displayformat)(T data) = nullptr) {
        _inOrderWalk(root, displayformat);
    }

    /**
     * this function prints the post-order walk sequence of the tree to the console
     * @param displayformat a pointer to the function that prints the data of the generic type to the console
     * <p>leave blank to use the default format
     * @example using a lambda function: @code
     *      treeInstance.postOrderWalk([}(int data){
     *          cout << data << ", ";
     *      });
     */
    void postOrderWalk(void (*displayformat)(T data) = nullptr) {
        _postOrderWalk(this->root, displayformat);
    }

    /**
     * this array returns the height of the binary tree
     * @return the height of the binary tree
     */
    int getHeight() {
        return root->height;
    }

    int nodesOnDepth(int depth) {
        int count = 0;
        _nodesOnDepth(depth, this->root, 0, count);
        return count;
    }

    bool isBST() {
        return _holdsBSTProperty(this->root);
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
        BSTNode<T>* nil = new BSTNode<T>; nil->setInternalNil();

        // converting to a complete binary tree

        unsigned nodeCount = pow(2, root->height + 1) - 1;
        for (unsigned int i = 0; i < nodeCount; i++) {
            if (i >= UINT32_MAX - 1) {
                std::cout << "too many nodes" << std::endl;
                return;
            }
            BSTNode<T>* node = level_queue.front(); level_queue.pop();
            if (node->left != nullptr) {
                level_queue.push(node->left);
            } else {
                level_queue.push(nil);
            }
            if (node->right != nullptr) {
                level_queue.push(node->right);
            } else {
                level_queue.push(nil);
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
                if (!completeBST[k]->isNilNode) {
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
#endif //BINARY_TREE_LAB_BINARY_TREE_H
