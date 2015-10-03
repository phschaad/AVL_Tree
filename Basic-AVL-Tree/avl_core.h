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
 */
typedef struct tree_node_s {
  int key;
  void *data;
  struct tree_node_s *left_child;
  struct tree_node_s *right_child;
} Node;

/*
 * Structure: avl_tree_s
 " ---------------------
 * Description:
 * The AVL tree itself. Used to make multiple instances of
 * The type AVL-Tree.
 *
 * Fields: height - Holds the total height of the tree.
 *         root - Pointer to the root of the tree.
 */
typedef struct avl_tree_s {
  int height, n_nodes;
  struct tree_node_s *root;
} AvlTree;

/*
 * ---------------------------
 * -- Function declaration. --
 * ---------------------------
 */

/*
 * Function: key_insert
 * --------------------
 * Description:
 * Create and insert a node directly in to a tree, 
 * according to its order-key. The function has an
 * integer return type for reporting wether or not
 * the insert was successful.
 *
 * Arguments: key - The identification key in the BST.
 *            tree - The corresponding tree.
 *
 * Returns: int 0 - insert failed.
 *              1 - insert was successful.
 *             -1 - fatal error.
 */
int key_insert(int key, AvlTree *tree);

/*
 * Function: has_key
 * -----------------
 * Descripton:
 * Has key checks for a specific key inside a
 * tree, returning 0 if it was not found, and
 * 1 if it was found.
 *
 * Arguments: key - The identification key in the BST.
 *            tree - The corresponding tree.
 *
 * Returns: int 0 - if not found.
 *              1 - if found.
 */
int has_key(int key, AvlTree *tree);

/*
 * Function: key_lookup
 * --------------------
 * Description: 
 * Key lookup function searches for a specific node
 * in the tree, according to it's direct order-key.
 * 
 * Arguments: key - The identification key in the BST.
 *            tree - The corresponding tree.
 *
 * Returns: Node - The node that was found while searching
 *                 for that key. (May be NULL). [POINTER]!
 */
Node * key_lookup(int key, AvlTree *tree);

/*
 * Functoin: get_height
 * --------------------
 * Description:
 * Returns the current total height of the tree.
 *
 * Arguments: tree - Pointer to the corresponding tree.
 *
 * Returns: int - height of the tree.
 *          -1 in case of failure. (tree does not exist.)
 */
int get_height(AvlTree *tree);

/*
 * Function: holds
 * ---------------
 * Description:
 * Returns the number of nodes in a tree.
 *
 * Arguments: tree - Pointer to the corresponding tree.
 *
 * Returns: int - the number of nodes in the tree.
 *          -1 in case of failure. (tree does not exist.)
 */
int holds(AvlTree *tree);

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

#endif /*  _AVL_CORE_H_ */
