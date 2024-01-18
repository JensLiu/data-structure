# Data Structure

💡 Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein. 2009. Introduction to
Algorithms, Third Edition (3rd. ed.). The MIT Press.

# Linked List

[See the project](https://github.com/JensLiu/data-structure/tree/main/linked_list)

💡 This implementation is a circular doubly linked list

### Operations

- `insertBefore`/`insertAfte` an `iterator`
- `pushFront` to the list
- `pushBack` to the list
- `find` an element
- `breakFree`(remove) the element at an iterator
- `erase` every element of the list
- `saveToFile`: save the list to a binary file
- `readFromFile`: read the binary file to a list
- `quickSort` the list

  👉 Example

    ```cpp
    // generate random numbers
    LinkedList<int> list;
    for (int i = 0; i < 1000000; i++) {
        list.pushBack((int)random());
    }
    
    // sort
    list.quicksort(list.begin(), list.end(), [](int i, int j) { return i < j; } );
    
    // test
    auto p = list.begin();
    auto p1 = p->data;
    p++;
    while (p != list.end()) {
        if (p1 > p->data) {
            throw std::runtime_error("sort failed");
        }
        p1 = p->data;
        p++;
    }
    std::cout << "\nsort success\n";
    return 0;
    ```

# Binary Tree

[See the project](https://github.com/JensLiu/data-structure/tree/main/binary_tree)

💡 Reference: CLRS : chap. 12-13

## `BSTNode` is a generic tree node for Binary Tree, BST, AVL Tree and Red-Black Tree

It contains generic metadata about its `parent`, `left` child, `right` child and its `key`

💡 For AVL tree, it stores its `height` for balancing purpose. It is updated on each operation

💡 For red-black tree, it stores its `nodeColour` and whether it `isNilNode`

💡 See `bst_node.h`

👀 It should be better named as `BTNode` rather than `BSTNode` …

```cpp
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
}
```

## `BinaryTree` is a generic binary tree

It only maintains its `root` node

💡 see `binary_tree.h`

```cpp
template <typename T>
class BinaryTree {

protected:
    BSTNode<T>* root;
...
}
```

### Some Operations

- check if this tree `isBST`
- doing recursive and iterative `preOrderWalk`, `inOrderWalk` and `postOrderWalk` sequence

- construct binary tree using pre-order and in-order sequences`preAndInWalkInsert`, or post-order and in-order
  sequence `postAndInWalkInsert`.

  👉 Example
    ```cpp
    BinaryTree<int> intBT;
    int preOrder[5] = {1, 2, 3, 4, 5};
    int inOrder[5] = {3, 2, 4, 1, 5};
    intBT.preAndInWalkInsert(preOrder, inOrder, 5);
    intBT.printTree(1); // arg: width
    ```
  ![construction](./doc/assets/tree_construction.png)

- print the binary tree in a tree-like manner `printTree`

  👉 Example
    ```cpp
    BinaryTree<char> charBT;
    charBT.preAndInWalkInsert("ABDGCEF", "DGBAECF", 7);
    charBT.printTree(1); // arg: width
    ```
  ![print](./doc/assets/tree_print.png)

## `BST` is a binary tree that holds the BST property
💡 see `bst.h`
```cpp
template <typename T>
class BST : public BinaryTree<T> {
...
}
```

Some important operations

- `insert` a key into the BST
- `deleteNode` from the BST
- `find` if a key exists
- `leftRotate` or `rightRotate`a node

## `AVL` tree is a self-balancing BST

💡 see `avl_tree.h`

💡 It calls `rebalance` after every `insert` and `delete`

👀 Example: insert

![insert](./doc/assets/avl_insert.png)

👀 Example: remove

![remove](./doc/assets/avl_remove.png)

## `RBTree` is a self-balancing BST

💡 see `re_tree.h`

👀 It holds a universal `nil` node as the child of every leaf node

```cpp
template <typename T>
class RBTree {
    BSTNode<T> *nil;
    BSTNode<T>* root;
...
}
```

👀 Only insert re-balance is implemented…

👀 Example: insert

![insert](./doc/assets/rb_insert.png)

# Graph

[See the project](https://github.com/JensLiu/data-structure/tree/main/graph)

💡 This implementation uses adjacency list

💡 Reference CLRS: chap. 22-24

## Structure Overview

![graph](./doc/assets/graph_structure.png)

💡 This structure separates the keys of the vertices (`VertexInfo`) from the ids (indices in the `VertexMap`) of the
vertices

💡 Deleting a vertex is expensive, it involves a complete scan in the adjacency list and a shift in the vertex map

💡 Optimisation: replace `std::vector` in the `VertexMap` with a hash map and a monotonically increasing counter to
assign ids.

## Some Operations

- `addVertex` to the graph
- get `idOfVertex` by its unique key (`VertexInfo`)
- `removeVertex` or `removeVertexById`
- `addEdge`or `addEdgeById` to the graph
- `findEdge` using `sourceId` and `destId` of the source and destination vertex
- `removeEdge` or `removeEdgeById`

## Algorithms

- Breadth-first search (`bfs`)
- Depth-first search(`dfs`)
- Dijkstra’s algorithm (`dijkstra`)
- Kruskal’s algorithm (`kruskal`)
- Prim’s algorithm (`prime`)

# Graph Visualisation using Qt

[See the project](https://github.com/JensLiu/data-structure/tree/main/graph_visualisation_lab)

Based on the Elastic Nodes Example project, the documentation is as follows
[Elastic Nodes Example | Qt Widgets 5.15.16](https://doc.qt.io/qt-5/qtwidgets-graphicsview-elasticnodes-example.html)

⚠️ Only the arrow of each edge changes colour </br>
Edges are overlapped since we are representing an undirected graph using a directed graph

- Depth-first search visualisation [demo video](https://youtu.be/cqomDOezHR4)
- Breadth-first search [demo video](https://youtu.be/8KfNZS-bva8)
- Kruskal [demo video](https://youtu.be/ZUjptrScf3Y)
- Prim’s algorithm [demo video](https://youtu.be/4Xm-g0DdI5g)
- Dijkstra’s algorithm [demo video](https://youtu.be/9Gd1DsD32mg?si=0ccBLgS_-HWF2sdT)
- Add and remove vertices and edges [demo video](https://youtu.be/0qTjdJhIVvk)
    
