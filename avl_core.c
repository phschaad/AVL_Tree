/* Basic AVL-Tree implementation - Core module */
/*
 * Author: Philipp Schaad
 * Creation Date: 011015 
 */

#include "avl_core.h"


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
int search_key(AvlTree *tree, int key, Node *node){
  // Safety-check for existence of the tree.
  if(tree == NULL || tree->root == NULL){
    return 0;
  }
  // If the tree exists, continue here.

  // Pointer to the "active" node in the search.
  Node *active = tree->root; // (Start at root).

  // Iterate over the tree.
  while(true){
    // Compare the key to the one of active.
    if(key < active->key){
      // The key would be to the left of active.
      if(active->left_child == NULL){
	// The tree does not contain the key.
	node = active; // Return the parent.
	return 0;
      }
      // Continue iteration.
      active = active->left_child;
    }else if(key > active->key){
      // The key would be to the right of active.
      if(active->right_child == NULL){
	// The tree does not contain the key.
	node = active; // Return the parent.
	return 0;
      }
      // Continue iteration.
      active = active->right_child;
    }else{
      // The active node contains the key!
      node = active; // Return active.
      return 1;
    }
  }

  // Safety fall-thru. Returns on fatal error.
  return -1;
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
  
}
