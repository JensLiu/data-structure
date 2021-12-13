#include "binary_tree.h"
#include "avl_tree.h"
#include "rb_tree.h"
using namespace std;
int main() {

    // test for vanilla binary tree-------------------------------------------------------

    // 1. Binary tree for primitive types
    BinaryTree<char> charBT;
    BinaryTree<int> intBT;

    // without the loss of generality,
    // we use post-order and in-order traversal sequence of a given type to initialise a binary tree
    // ( cannot create a binary tree of custom defined type using a string )
    int preOrder[5] = {1, 2, 3, 4, 5};
    int inOrder[5] = {3, 2, 4, 1, 5};
    intBT.preAndInWalkInsert(preOrder, inOrder, 5);
    intBT.postOrderWalk();
    cout << endl;
    intBT.postOrderWalk_iterative();

    intBT.printTree(1);

    for (int i = 0; i <= intBT.getHeight(); i++) {
        cout << "nodes on depth " << i << ": " << intBT.nodesOnDepth(i) << endl;
    }

    charBT.preAndInWalkInsert("ABDGCEF", "DGBAECF", 7);
    charBT.printTree(1);
    charBT.inOrderWalk_iterative();
    cout << endl;
    cout << "pre-order walk, recursive: ";charBT.preOrderWalk(); cout << endl;
    cout << "pre-order walk, iterative: "; charBT.preOrderWalk_iterative(); cout << endl;
    cout << "post-order walk, recursive: "; charBT.postOrderWalk(); cout << endl;
    cout << "post-order walk, iterative: "; charBT.postOrderWalk_iterative(); cout << endl;
    cout << "tree height: "; charBT.getHeight(); cout << endl;
    BinaryTree<char> t2(charBT);
    cout << "pre-order walk for deep copied tree: "; charBT.preOrderWalk(); cout << endl;


    // test for AVL tree-----------------------------------------------------------------
    AVL<int> avl;

    cout << "test for AVL tree" << endl;
    cout << "insertion test" << endl;
    cout << "AVL insert 1: -> "; avl.insert(1); cout << "is BST: " << avl.isBST() << endl; avl.printTree(1);
    cout << "AVL insert 2: -> "; avl.insert(2); cout << "is BST: " << avl.isBST() << endl; avl.printTree(1);
    cout << "AVL insert 3: -> "; avl.insert(3); cout << "is BST: "<< avl.isBST() << endl; avl.printTree(1);
    cout << "AVL insert 4: -> "; avl.insert(4); cout << "is BST: " << avl.isBST() << endl; avl.printTree(1);
    cout << "AVL insert 5: -> "; avl.insert(5); cout << "is BST: " << avl.isBST() << endl; avl.printTree(1);
    cout << "AVL insert 6: -> "; avl.insert(6); cout << "is BST: " << avl.isBST() << endl; avl.printTree(1);
    cout << "AVL insert 7: -> "; avl.insert(7); cout << "is BST: " << avl.isBST() << endl; avl.printTree(1);


    cout << "AVL remove 4: -> ";
    avl.deleteNode_iterative(4); cout << "is BST: " << avl.isBST() << endl; avl.printTree(1);
    cout << "AVL remove 5: -> "; avl.deleteNode(5); cout << "is BST: " << avl.isBST() << endl; avl.printTree(1);
    cout << "AVL remove 6: -> "; avl.deleteNode(6); cout << "is BST: " << avl.isBST() << endl; avl.printTree(1);
    cout << "AVL remove 2: -> "; avl.deleteNode(2); cout << "is BST: " << avl.isBST() << endl; avl.printTree(1);
    cout << "AVL remove 3: -> "; avl.deleteNode(3); cout << "is BST: " << avl.isBST() << endl; avl.printTree(1);
    cout << "AVL remove 7: -> "; avl.deleteNode(7); cout << "is BST: " << avl.isBST() << endl; avl.printTree(1);
    cout << "AVL remove 1: -> "; avl.deleteNode(1); cout << "is BST: " << avl.isBST() << endl; avl.printTree(1);


    cout << "test for AVL tree" << endl;
    cout << "insertion test" << endl;
    cout << "AVL insert 1: -> "; avl.insert(1); avl.postOrderWalk_iterative(); cout << endl; avl.printTree(1);
    cout << "AVL insert 2: -> "; avl.insert(2); avl.postOrderWalk_iterative(); cout << endl; avl.printTree(1);
    cout << "AVL insert 3: -> "; avl.insert(3); avl.postOrderWalk_iterative(); cout << endl; avl.printTree(1);
    cout << "AVL insert 4: -> "; avl.insert(4); avl.postOrderWalk_iterative(); cout << endl; avl.printTree(1);
    cout << "AVL insert 5: -> "; avl.insert(5); avl.postOrderWalk_iterative(); cout << endl; avl.printTree(1);
    cout << "AVL insert 6: -> "; avl.insert(6); avl.postOrderWalk_iterative(); cout << endl; avl.printTree(1);
    cout << "AVL insert 7: -> "; avl.insert(7); avl.postOrderWalk_iterative(); cout << endl; avl.printTree(1);

    RBTree<int> rb;
    cout << "RB insert 1: ->"; rb.insert(1); rb.preOrderWalk(); cout << endl; rb.printTree(1); cout << endl;
    cout << "RB insert 2: ->"; rb.insert(2); rb.preOrderWalk(); cout << endl; rb.printTree(1); cout << endl;
    cout << "RB insert 3: ->"; rb.insert(3); rb.preOrderWalk(); cout << endl; rb.printTree(1); cout << endl;
    cout << "RB insert 4: ->"; rb.insert(4); rb.preOrderWalk(); cout << endl; rb.printTree(1); cout << endl;
    cout << "RB insert 5: ->"; rb.insert(5); rb.preOrderWalk(); cout << endl; rb.printTree(1); cout << endl;
    cout << "RB insert 6: ->"; rb.insert(6); rb.preOrderWalk(); cout << endl; rb.printTree(1); cout << endl;
    cout << "RB insert 7: ->"; rb.insert(7); rb.preOrderWalk(); cout << endl; rb.printTree(1); cout << endl;
    cout << "RB insert 8: ->"; rb.insert(8); rb.preOrderWalk(); cout << endl; rb.printTree(1); cout << endl;
    cout << "RB insert 8: ->"; rb.insert(9); rb.preOrderWalk(); cout << endl; rb.printTree(1); cout << endl;

    return 0;
}