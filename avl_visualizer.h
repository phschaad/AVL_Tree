/* Basic AVL-Tree implementation - Visualization module */ 
/*
 * Author: Philipp Schaad
 * Creation Date: 151015
 * 
 * # ------------------------------------------- #
 * # ---------------- COPYRIGHT ---------------- #
 * # ------------------------------------------- #
 * # This file is part of the AVL-Tree project.  #
 * # Author of this project is Philipp Schaad.   #
 * # For additional Licensing information see    #
 * # the provided LICENSE file. For contact      #
 * # information see the README.                 #
 * # ------------------------------------------- #
 *
 * Description:
 * This is the visualizer module of the AVL-Tree implementation.
 * This module provides:
 *     - Visualization of the AVL-Tree.
 *
 * Exit Code Index:
 *     > 0:  Successful Execution.
 */

#ifndef __AVL_VISUALIZER_H_
#define __AVL_VISUALIZER_H_

#include "avl_core.h"

#include <math.h>

/*
 * Function: visualize
 * -------------------
 * Description:
 * Visualize a binary search tree by printing it
 * to the console in layers representing each in-
 * dividual height-layer of the tree.
 * 
 * Arguments: tree - The avl tree to visualize.
 *
 * Returns: void
 */
extern void visualize(AvlTree *tree);

/*
 * Function: assemble_node_list
 * ----------------------------
 * Description:
 * Build an array containing all the nodes of the avl
 * tree. (Recursively)
 * 
 * Arguments: node - currently active node in recursion.
 *            list - the list to fill. 
 *            t_index - index of the current node in the tree.
 * 
 * Returns: void
 */
extern void assemble_node_list(Node *node, int *list, int t_index);

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
extern void traverse_inorder_console(Node *node);

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
extern void traverse_postorder_console(Node *node);

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
extern void traverse_preorder_console(Node *node);

#endif /* __AVL_VISUALIZER_H_ */
