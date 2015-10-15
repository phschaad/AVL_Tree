/* Basic AVL-Tree implementation - Core module */
/*
 * Author: Philipp Schaad
 * Creation Date: 011015 
 * 
 * Description:
 * This is the core module of an AVL-Tree implementation.
 * This module provides:
 *     - Basic AVL-Tree structure
 *     - Insertion, Deletion and Lookup in AVL-Tree
 *     - Traversal and visualization of AVL-Tree(s).
 *
 * Exit Code Index:
 *     > 0:  Successful Execution.
 *     > 1:  Memory Allocation Failure.
 *     > 2:  Critical Error in core functions. 
 */

#ifndef __AVL_CORE_H_
#define __AVL_CORE_H_

/*
 * -----------------------------
 * -- Structures and typedefs --
 * -----------------------------
 */

/*
 * Structure: tree_node_s
 * ----------------------
 * Description:
 * Basic element of a binary search (AVL) tree. A simple tree
 * node holding:
 *
 * Fields: key - Used for ordering. Holds order of the node.
 *         data - Pointer to the actual data stored in the node.
 *         height - Holds the height value of the node.
 *         left-child - Pointer to the left child node of the node.
 *         right-child - Pointer to the right child node of the node.
 *         parent - Pointer to the parent node of the node.
 */
typedef struct tree_node_s {
  int key, height;
  void *data;
  struct tree_node_s *left_child, *right_child, *parent;
} Node;

/*
 * Structure: avl_tree_s
 * ---------------------
 * Description:
 * The AVL tree itself. Used to make multiple instances of
 * The type AVL-Tree.
 *
 * Fields: height - Holds the total height of the tree.
 *         root - Pointer to the root of the tree.
 */
typedef struct avl_tree_s {
  int height, number_of_nodes;
  struct tree_node_s *root;
} AvlTree;

/*
 * ----------------------------
 * -- Function declarations. --
 * ----------------------------
 */

/*
 * Function: make_tree_from_node
 * -----------------------------
 * Description:
 * Creates a new tree from a pre-existing node.
 *
 * Arguments: node - The pre-existing node.
 * 
 * Returns: Pointer to the newly created tree.
 */
extern AvlTree * make_tree_from_node(Node *node);

/*
 * Function: make_tree_empty
 * -------------------------
 * Description:
 * Create and allocate a new tree, containing no
 * nodes.
 * 
 * Arguments: none
 *
 * Returns: Pointer to the newly created tree.
 */
extern AvlTree * make_tree_empty();

/*
 * Function: make_node_empty
 * -------------------------
 * Description: 
 * This function creates and allocates memory for 
 * a new node, containing no data. It takes a key
 * argument.
 *
 * Arguments: key - The order key the node has.
 * 
 * Returns: Node pointer to the new node.
 */
extern Node * make_node_empty(int key);

/*
 * Function: upin
 * --------------
 * Description:
 * This method is called after insertion of a node
 * and walks up the tree from the freshly inserted
 * node, checking the avl condition on every point.
 * If the AVL condition is violated at a point, it
 * calls the corresponding rotations to fix it.
 *
 * Arguments: node - The node from which upin is called. 
 *            tree - The tree operating in.
 * 
 * Returns: void 
 */
extern void upin(AvlTree *tree, Node *node);

/*
 * Function: balance
 * -----------------
 * Description:
 * Figure out the balance of a node.
 * Scan the height of the children trees to calculate it.
 *
 * Arguments: node - The node in question.
 * 
 * Returns: the balance.
 */
extern int balance(Node *node);

/*
 * Function: rotate_right
 * ----------------------
 * Description:
 * Execute a single righthand rotation around
 * a given node.
 *
 * Arguments: node - The node to rotate.
 *            tree - The tree operating in.
 *
 * Returns: void 
 */
extern void rotate_right(AvlTree *tree, Node *node);

/*
 * Function: rotate_left
 * ---------------------
 * Description:
 * Execute a single lefthand rotation around
 * a given node. 
 * 
 * Arguments: node - The node to rotate.
 *            tree - The tree operating in.
 *
 * Returns: void
 */
extern void rotate_left(AvlTree *tree, Node *node);

/*
 * Function: search_by_key
 * -----------------------
 * Description:
 * Search for a node in the tree. If the node is found,
 * return a truthy and a pointer to the node-location.
 * If not, return a falsey and point to the node which
 * would represent it's parent, if it were in the tree.
 *
 * Arguments: key  - order key to search for.
 *            node - will point to node in question.
 *            tree - The tree to search in. 
 * 
 * Returns: 1  - If node has been found.
 *          0  - If the node was not found.
 */
extern int search_by_key(int key, AvlTree *tree, Node **node);

/*
 * Function: key_insert_new
 * ------------------------
 * Description:
 * Insert a node in to the tree (if it does not
 * exist already) according to its order key.
 * The node will initially not contain any data.
 * 
 * Arguments: key  - The order key to use.
 *            tree - The tree to insert into.
 *
 * Returns: 1  - On successful insertion.
 *          0  - If insertion failed.
 */
extern int key_insert_new(int key, AvlTree *tree);

/*
 * Function: key_delete
 * --------------------
 * Description:
 * This function, for a given key, searches the node
 * with that order key in the given tree and tries
 * to delete it. If the key could not be found, the
 * function returns 0, otherwise it returns 1 after 
 * deletion.
 *
 * Arguments: key - The key to search and delete.
 *            tree - The tree to search and delete in.
 *
 * Returns: 1 - Successful deletion.
 *          0 - Deletion unsuccessful (key not found).
 */
extern int key_delete(int key, AvlTree *tree);

/*
 * Function: max
 * -------------
 * Description:
 * Simple helper function to determine the max of two
 * Integer numbers.
 *
 * Arguments: a - first value.
 *            b - second value.
 *
 * Returns: the maximum of the two.
 */
extern int max(int a, int b);

#endif /*  __AVL_CORE_H_ */
