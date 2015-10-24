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

#include "avl_visualizer.h"
#include "avl_core.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

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
void visualize(AvlTree *tree){
  // Check arguments.
  assert(tree != NULL);

  // If the tree is empty, visualize it with a {empty} tag.
  if(tree->root == NULL){
    printf("{empty}\n");
    return;
  }
  
  // Total number of layers in the tree.
  int layers = tree->height + 1;

  // Figure out the maximum possible ammount of nodes.
  int max_n_nodes = 0;
  for(int i = 0; i < layers; i++){
    max_n_nodes += pow(2, i);
  }

  // Fill the node list with all -1. 
  int node_list[max_n_nodes];
  for(int i = 0; i < max_n_nodes; i++){
    node_list[i] = -1;
  }

  // Assemble the node list from the tree.
  assemble_node_list(tree->root, node_list, 1);

  // Iterate through list, printing it out in tree format.
  int level = 0;
  int max = 1;
  int max_prev = 0;
  for(int i = 0; i < (pow(2, tree->height + 1) - 2); i++){
    printf(" "); // 1 whitespace.
  }
  for(int i = 0; i < max_n_nodes; i++){
    // Calculate number of whitespaces between nodes. 
    int num_spaces = pow(2, tree->height - level + 2) - 3;
    
    if(node_list[i] == -1){
      // -1 means no node, so print x.
      printf(" x "); // print x.
    }else{
      // Print key of the node at that index.
      if(node_list[i] < 100) printf(" ");
      printf("%d", node_list[i]);
      if(node_list[i] < 10) printf(" ");
    }

    // Print whitespace between nodes.
    for(int j = 0; j < num_spaces; j++){
      printf(" "); // 1 whitespace.
    }

    // Start a new line after a level is complete.
    if(!(i < (max - 1))){
      printf("\n"); // New line.
      // Print whitespaces at start of line.
      for(int j = 0; j < (pow(2, tree->height - level) - 2); j++){
	printf(" "); // 1 whitespace. 
      }
      level++; // Increase level.
      max_prev = max;
      // Update the size of the level.
      max = pow(2, level) + max_prev;
    }
  }
}

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
void assemble_node_list(Node *node, int *list, int t_index){
  // Check arguments
  assert(node != NULL);
  assert(list != NULL);

  // Put the key of the current node at the correct poistion.
  list[t_index - 1] = node->key;

  // Repeat for left child if it exists.
  if(node->left_child){
    assemble_node_list(node->left_child, list, t_index * 2);
  }

  // Repeat for right child if it exists.
  if(node->right_child){
    assemble_node_list(node->right_child, list, (t_index * 2) + 1);
  }
}

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
void traverse_inorder_console(Node *node){
  // Check if the node exists, if yes, do traversal.
  if(node != NULL){
    traverse_inorder_console(node->left_child);
    printf("%d ", node->key);
    traverse_inorder_console(node->right_child);
  }
}

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
void traverse_postorder_console(Node *node){
  // Check if node exists, if yes, do traversal.
  if(node != NULL){
    traverse_postorder_console(node->left_child);
    traverse_postorder_console(node->right_child);
    printf("%d ", node->key);
  }
}

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
void traverse_preorder_console(Node *node){
  // Check if node exists, if yes, do traversal.
  if(node != NULL){
    printf("%d ", node->key);
    traverse_preorder_console(node->left_child);
    traverse_preorder_console(node->right_child);
  }
}
