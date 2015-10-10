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
 * Function: search_key
 * --------------------
 * Description:
 * Searches a node in a tree, according to 
 * its order key. If the key is found, return
 * one, if not, return 0. The function takes
 * a node-pointer as an argument and assigns
 * it the node, if it was found. If not, the
 * Pointer will point to the parent node, of 
 * where the node would have been.
 *
 * Arguments: tree - The AVL tree to search.
 *            key  - The order key of the to-search node
 *            node - The pointer to the node.
 *
 * Returns:   1    - If node found.
 *            0    - If node not found.
 *            -1   - Fatal error.
 */
int search_key(AvlTree *tree, int key, Node *node);

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
