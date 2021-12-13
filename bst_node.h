//
// Created by Jens on 18.11.2021.
//

#ifndef BINARY_TREE_LAB_BST_NODE_H
#define BINARY_TREE_LAB_BST_NODE_H

template <typename T>
class BSTNode {
public:
    enum Colour{ BLACK = 0, RED};
public:
    BSTNode<T>* parent;
    BSTNode<T>* left;
    BSTNode<T>* right;
    T key;
    int height;

    // this is for red-black tree, ignore when it's not the case
    Colour nodeColour;
    // this is a flag for nil node that symbols the lack of node, ignore when it's not the case
    bool isNilNode;

public:
    /**
     * class constructor
     * @param key
     */
    BSTNode(T key) {
        this->key = key;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        height = 0;
        // extended attributes that may not be used
        isNilNode = false;
        nodeColour = RED;
    }

    /**
     * class constructor
     */
    BSTNode() {
        this->key = 0;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        height = 0;
        // extended attributes that may not be used
        isNilNode = false;
        nodeColour = RED;
    }

    /**
     * this function sets the node to nil, but both child of the node are null pointers
     * that can be a sentinel node on which to stop
     */
    void setNil() {
        // set the node to be a nil node, this cannot be undone
        this->isNilNode = true;
        this->left = nullptr;
        this->right = nullptr;
        this->nodeColour = BLACK;
    }

    /**
     * this function sets the node to nil, but both child of the node are null pointers
     * that can be a sentinel node on which to stop
     */
    void setTermenalNil() {
        setNil();
    }

    /**
     * this function sets the node to nil and reference itself as its left and right child
     * it can be useful as the placeholder when generating a complete / almost-complete binary tree
     * because of its self-reference. When generating, it doesn't give a flag on when to stop
     * so you have to set a counter that stops at the (2^h)th nodes
     */
    void setInternalNil() {
        this->isNilNode = true;
        this->left = this;
        this->right = this;
        this->nodeColour = BLACK;
    }

    /**
     * this function checks if the node is nil node
     * it can be internal nil node that is self-referenced or
     * terminal nil that's not
     */
    bool isNil() {
        return this->isNilNode;
    }

    /**
     * this function checks if the node is an internal nil node
     */
    bool isInternalNil() {
        return (this->isNilNode && this->left == this && this->right == this);
    }

    /**
     * this function checks if the node is a terminal nil node
     */
    bool isTermenalNil() {
        return (this->left == nullptr && this->right == nullptr);
    }

    void colourRed() {
        this->nodeColour = RED;
    }

    void colourBlack() {
        this->nodeColour = BLACK;
    }
};

/**
 * this function returns the height of the node
 * @tparam T
 * @param node
 * @return
 */
template <typename T>
int nodeHeight(BSTNode<T>* node) {
    return (node == nullptr) ? -1 : node->height;
}

/**
 * this function updates the height of the node
 * assuming that the height of its children are correct
 * @tparam T
 * @param node
 */
template <typename T>
void updateHeight(BSTNode<T>* node) {
    node->height = max(nodeHeight(node->left), nodeHeight(node->right)) + 1;
}
#endif //BINARY_TREE_LAB_BST_NODE_H
