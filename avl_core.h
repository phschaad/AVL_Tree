/* Basic AVL-Tree implementation - Core module */
/*
 * Author: Philipp Schaad
 * Creation Date: 011015 
 */

#ifndef _AVL_CORE_H_
#define _AVL_CORE_H_

#include <stdio.h>
#include <stdlib.h>

/*
 * -----------------------------
 * -- Structures and typedefs --
 * -----------------------------
 */

/*
 * Defining booleans, for simpler handling of
 * true/false operations. Just a helper.
 */
typedef enum {
  false,
  true
} bool; // Going off convention with capitalization for convenience.

/*
 * Structure: tree_node_s
 * ----------------------
 * Description:
 * Basic element of a binary search (AVL) tree. A simple tree
 * node holding:
 *
 * Fields: key - Used for ordering. Holds order of the node.
 *         data - Pointer to the actual data stored in the node.
 *         left-child - Pointer to the left child node of the node.
 *         right-child - Pointer to the right child node of the node.
 *         balance - Holds the current balance factor of the node.
 */
typedef struct tree_node_s {
  int key, balance;
  void *data;
  struct tree_node_s *left_child, *right_child;
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
AvlTree * make_tree_from_node(Node *node);

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
AvlTree * make_tree_empty();

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
Node * make_node_empty(int key);

/*
 * Function: search_node
 * ---------------------
 * Description:
 * Search for a node in the tree. If the node is found,
 * return a truthy and a pointer to the node-location.
 * If not, return a falsey and point to the node which
 * would represent it's parent, if it were in the tree
 * (this is used for node insertion in to the tree.)
 *
 * Arguments: key  - order key to search for.
 *            node - will point to node in question.
 *            tree - The tree to search in. 
 * 
 * Returns: 1  - If node has been found.
 *          0  - If the node was not found.
 *          -1 - Fatal error.
 */
int search_node(int key, AvlTree *tree, Node **node);

/*
 * Function: insert_node_key
 * -------------------------
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
 *          -1 - Fatal error.
 */
int insert_node_key(int key, AvlTree *tree);

/*
 * Function: traverse_inorder_console
 * ----------------------------------
 * Description:
 * This function does a (recursive) inorder traversal
 * of the AVL-Tree. The ouput is console-based, being
 * displayed as a one-line string.
 * 
 * Arguments: node - The node the recursion is at.
 * 
 * Returns: void
 */
void traverse_inorder_console(Node *node);

/*
 * Function: travere_postorder_console
 * -----------------------------------
 * Description:
 * This function does a (recursive) postorder traversal
 * of the AVL-Tree. The ouput is console-based, being
 * displayed as a one-line string.
 * 
 * Arguments: node - The node the recursion is at.
 * 
 * Returns: void
 */
void traverse_postorder_console(Node *node);

/*
 * Function: travere_preorder_console
 * ----------------------------------
 * Description:
 * This function does a (recursive) preorder traversal
 * of the AVL-Tree. The ouput is console-based, being
 * displayed as a one-line string.
 * 
 * Arguments: node - The node the recursion is at.
 * 
 * Returns: void
 */
void traverse_preorder_console(Node *node);

#endif /*  _AVL_CORE_H_ */
