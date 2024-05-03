# RedBlackTree

## About RedBlackTree:

#### The following information is taken from [the Geeks for Geeks RBT page](https://www.geeksforgeeks.org/introduction-to-red-black-tree/?ref=lbp)

### What is a Red Black Tree?
Red-Black tree is a **`binary search tree`** in which every node is colored with either red or black. It is a type of self balancing binary search tree. It has a good efficient worst case running time complexity. 

### Properties of Red Black Tree:
The Red-Black tree satisfies all the properties of binary search tree in addition to that it satisfies following additional properties:

1. **`Root property`**: The root is black.

2. **`External property:`** Every leaf (Leaf is a NULL child of a node) is black in Red-Black tree.

3. **`Internal property`**: The children of a red node are black. Hence possible parent of red node is a black node.

4. **`Depth property`**: All the leaves have the same black depth.

5. **`Path property`**: Every simple path from root to descendant leaf node contains same number of black nodes. 

The result of all these above-mentioned properties is that the Red-Black tree is roughly balanced.

### Rules That Every Red-Black Tree Follows:
1. Every node has a color either red or black.

2. The root of the tree is always black.

3. There are no two adjacent red nodes (A red node cannot have a red parent or red child).

4. Every path from a node (including root) to any of its descendants NULL nodes has the same number of black nodes.

5. Every leaf (**`e.i. NULL node`**) must be colored **`BLACK`**.

### Why Red-Black Trees?
The height of a Red-Black tree is always O(log n) where n is the number of nodes in the tree. This means every operation has a time complexity of O(log n).
