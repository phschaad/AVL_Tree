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
  int height;
  struct tree_node_s *root;
} AvlTree;

/*
 * Function: key_insert
 * --------------------
 * Description:
 * Key insert function directly takes an integer
 * key as an argument and creates a new node with order
 * of that key. The new node will hold no data. After 
 * creation, it will be inserted in to the correct
 * position in the already existing BST.
 *
 * Arguments: key - The identification key in the BST.
 *
 * Returns: 1 on successful insertion
 *          0 if insertion failed {eg: key already in tree}
 */
int key_insert(int key);

/*
 * Function: key_delete
 * --------------------
 * Description:
 * Key delete function searches for a specific node
 * in the tree, directly according to its order-key.
 * If a node has been found, it will be removed from
 * the tree, returning a truthy. If the node can not 
 * be found, the function returns a falsey.
 *
 * Arguments: key - The identification key in the BST.
 *
 * Returns: 1 if the deletion was successful.
 *          0 if the deletion failed. {eg. node not found}
 */
int key_delete(int key);

/*
 * Function: has_key
 * -----------------
 * Description: 
 * Has key function searches for a specific node
 * in the tree, according to it's direct order-key.
 * 
 * Arguments: key - The identification key in the BST.
 *
 * Returns: 1 if the key has been found
 *          0 if there is no such key in the BST.
 */
int has(int key);

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
 */
int get_height(AvlTree *tree);

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
