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

#include "avl_core.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
AvlTree * make_tree_from_node(Node *node){
  // Check arguments.
  assert(node != NULL);
  
  // Allocate space for the new tree.
  AvlTree *tree = (AvlTree *)malloc(sizeof(AvlTree));
  if(tree == NULL){
    // Memory allocation failed, report and exit.
    printf("Memory allocation failed while creating a new tree from a node.\n");
    exit(1); // Throw memory allocation error.
  }

  tree->root = node; // Assign root.
  // Set the correct tree atributes.
  tree->height = 0;
  tree->number_of_nodes = 1;
  return tree;
}

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
AvlTree * make_tree_empty(){
  // Allocate memory.
  AvlTree *new_tree = (AvlTree *)malloc(sizeof(AvlTree));
  if(new_tree == NULL){
    // Memory allocation failed, report and exit.
    printf("Memory allocation failed while creating an empty tree.\n");
    exit(1); // Throw memory allocation error.
  }

  // Set the correct tree attributes.
  new_tree->root = NULL;
  new_tree->height = -1; // Represents an empty tree.
  new_tree->number_of_nodes = 0;
  return new_tree;
}

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
Node * make_node_empty(int key){
  // Allocate memory for the new node.
  Node *new_node = (Node *)malloc(sizeof(Node));
  if(new_node == NULL){
    // Memory allocation failed, report and exit.
    printf("Memory allocation failed while generating a new empty node.\n");
    exit(1); // Throw memory allocation error. 
  }

  // Set correct node attributes (for empty node).
  new_node->key = key;
  new_node->data = NULL;
  new_node->left_child = new_node->right_child = new_node->parent = NULL;
  new_node->height = 0;
  return new_node;
}

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
void upin(AvlTree *tree, Node *node){
  // Check arguments.
  assert(tree != NULL);
  assert(node != NULL);

  // Figure out the balance of the node.
  int bal = balance(node);
  
  // End upin procedure if root is reached.
  if(node->parent == NULL){
    return;
  }

  // Pointer to the parent node.
  Node *parent = node->parent;

  // Figure out the balance of it's parent.
  int p_bal = balance(parent);

  // Check balance for correctness, rotating if necessary.
  if(node->key < parent->key){
    if(p_bal == 0){
      // Exit upin if the parent balance is 0.
      return;
    }else if(p_bal == -1){
      // Continue upin at the parent.
      upin(tree, parent);
    }else if(p_bal < -1){
      if(bal == -1){
	// Do a single right rotation.
	rotate_right(tree, parent);
      }else if(bal == 1){
	// Do a double rotation (left, right).
	rotate_left(tree, parent->left_child);
	rotate_right(tree, parent);
      }else{
	// This should not be reached.
	printf("Critical error occured in upin procedure.\n");
	exit(2);
      }
    }else{
      // This should not be reached.
      printf("Critical error occured in upin procedure.\n");
      exit(2);
    }
  }else{
    if(p_bal <= 0){
      // Exit upin if the parent balance is 0.
      return;
    }else if(p_bal == 1){
      // Continue upin at the parent. 
      upin(tree, parent);
    }else if(p_bal > 1){
      if(bal == 1){
	// Do a single left rotation. 
	rotate_left(tree, parent);
      }else if(bal == -1){
	// Do a double rotation (right, left).
	rotate_right(tree, parent->right_child);
	rotate_left(tree, parent);
      }else{
	// This should not be reached.
	printf("Critical error occured in upin procedure.\n");
	exit(2);
      }
    }else{
      // This should not be reached.
      printf("Critical error occured in upin procedure.\n");
      exit(2);
    }
  }
}

/*
 * Function: upout
 * ---------------
 * Description:
 * This method is called after deletion of a node
 * and walks up the tree from the deleted
 * node, checking the avl condition on every point.
 * If the AVL condition is violated at a point, it
 * calls the corresponding rotations to fix it.
 *
 * Arguments: node - The node from which upout is called. 
 *            tree - The tree operating in.
 * 
 * Returns: void 
 */
void upout(AvlTree *tree, Node *node){
  // Check arguments.
  assert(tree != NULL);
  assert(node != NULL);

  // Keep track of the parent of the node.
  Node *parent = node->parent;
  
  // Get the balance of the current node.
  int bal = balance(node);

  if(bal < -1){
    // The node has a left-heavy imbalance.

    // Figure out the balance of its left child.
    int l_bal = balance(node->left_child);

    if(l_bal == -1){
      // Double left heavy imbalance. Fix by single right rotation.
      rotate_right(tree, node);
    }else if(l_bal == 1){
      // Left-Right imbalance. Fix with a left-right rotation.
      rotate_left(tree, node->left_child);
      rotate_right(tree, node);
    }else{
      rotate_right(tree, node);
    }
  }else if(bal > 1){
    // The node has a right-heavy imbalance.

    // Figure out the balance of its right child.
    int r_bal = balance(node->right_child);

    if(r_bal == 1){
      // Double right heavy imbalance. Fix with a single left rotation.
      rotate_left(tree, node);
    }else if(r_bal == -1){
      // Right-Left imbalance. Fix with a right-left rotation.
      rotate_right(tree, node->right_child);
      rotate_left(tree, node);
    }else{
      rotate_left(tree, node);
    }
  }

  // Continue upwards traversal.
  if(parent) upout(tree, parent);
}

/*
 * Function: get_height
 * --------------------
 * Description:
 * Calculates and returns the height of the given
 * Node. This does not adapt the height of its
 * children, so if those are off, the new height is
 * also going to be off! This is to conserve computational
 * effort. 
 * 
 * Arguments: node - The node to which to calculate the height.
 * 
 * Returns: The height of node.
 */
int get_height(Node *node){
  // Check arguments.
  assert(node != NULL);

  // The base heights for no children.
  int l_height = -1;
  int r_height = -1;
  // Update children's height if they exists.
  if(node->left_child) l_height = node->left_child->height;
  if(node->right_child) r_height = node->right_child->height;
  
  // Calculate and return the correct height.
  return get_int_max(l_height, r_height) + 1;
}

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
int balance(Node *node){
  // Check arguments.
  assert(node != NULL);

  // The base heights for no children.
  int l_height = -1;
  int r_height = -1;
  // Update children's height if they exists.
  if(node->left_child) l_height = node->left_child->height;
  if(node->right_child) r_height = node->right_child->height;

  // Update the current node's height.
  node->height = get_int_max(l_height, r_height) + 1;

  // Return the balance (height difference).
  return r_height - l_height;
}

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
void rotate_right(AvlTree *tree, Node *node){
  // Check arguments.
  assert(tree != NULL);
  assert(node != NULL);

  // Pointer to keep track of the second node in rotation.
  Node *l_child = node->left_child;

  // Do rotation.
  if(node->parent == NULL){
    // Operating on root.
    tree->root = l_child;
    l_child->parent = NULL;
  }else{
    // Give the parent its new child.
    if(node->key < node->parent->key){
      // We are left child.
      node->parent->left_child = l_child;
    }else{
      // We are right child.
      node->parent->right_child = l_child;
    }
    // Adapt the parent.
    l_child->parent = node->parent;
  }
  // Rearrange the children nodes.
  node->left_child = l_child->right_child;
  // If a child is there, adapt its parent.
  if(l_child->right_child) l_child->right_child->parent = node;
  l_child->right_child = node;
  node->parent = l_child;

  // Update the heights.
  if(node){
    node->height = get_height(node);
  }
  if(l_child){
    if(l_child->left_child){
      l_child->left_child->height = get_height(l_child->left_child);
    }
    l_child->height = get_height(l_child);
  }
}

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
void rotate_left(AvlTree *tree, Node *node){
  // Check arguments.
  assert(tree != NULL);
  assert(node != NULL);

  // Pointer to keep track of the second node in rotation.
  Node *r_child = node->right_child;

  // Do rotation.
  if(node->parent == NULL){
    // Operating on root.
    tree->root = r_child;
    r_child->parent = NULL;
  }else{
    // Give the parent its new child.
    if(node->key < node->parent->key){
      // We are left child.
      node->parent->left_child = r_child;
    }else{
      // We are right child.
      node->parent->right_child = r_child;
    }
    // Adapt the parent.
    r_child->parent = node->parent;
  }
  // Rearrange the children nodes.
  node->right_child = r_child->left_child;
  // If a child is there, adapt its parent.
  if(r_child->left_child) r_child->left_child->parent = node;
  r_child->left_child = node;
  node->parent = r_child;

  // Update the heights.
  if(node){
    node->height = get_height(node);
  }
  if(r_child){
    if(r_child->right_child){
      r_child->right_child->height = get_height(r_child->right_child);
    }
    r_child->height = get_height(r_child);
  }
}

/*
 * Function: search_by_key
 * -------------------------
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
int search_by_key(int key, AvlTree *tree, Node **node){
  // Check arguments.
  assert(tree != NULL);
  assert(node != NULL);
  
  // Check if the tree is empty.
  if(tree->root == NULL){
    // Return a NULL-pointer on the node, and falsy.
    *node = NULL;
    return 0;
  }

  // Start traversing the tree.
  *node = tree->root;
  while(1){
    if(key < (*node)->key){
      // Continue search to the left of the node.
      if((*node)->left_child == NULL){
	// Node not in tree, return.
	return 0;
      }
      // Continue traversal.
      *node = (*node)->left_child;
    }else if(key > (*node)->key){
      // Continue search to the right of the node.
      if((*node)->right_child == NULL){
	// Node is not in tree, return.
	return 0;
      }
      // Continue traversal.
      *node = (*node)->right_child;
    }else{
      // Found the node, return.
      return 1;
    }
  }

  // This should be unreachable code. Error if reached.
  printf("Critical error occured while searching for a node.\n");
  exit(2); // Exit with code 2. See Error index for details.
}

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
int key_insert_new(int key, AvlTree *tree){
  assert(tree != NULL); // Check arguments.

  // The new node.
  Node *new_node = make_node_empty(key);
  
  if(tree->root == NULL){
    // Tree is empty, make the new node the root.
    tree->root = new_node;
    new_node->parent = NULL;
    // Adapt the height of the tree.
    tree->height = 0;
    // Increment number of nodes in tree.
    tree->number_of_nodes++;
    return 1;
  }else{
    // Traverse the tree.
    // active keeps track of the current traversal "index".
    Node *active = tree->root;
    
    while(1){
      if(key < active->key){
	// New node is expected to left of active.
	if(active->left_child == NULL){
	  // Insert to the left of active.
	  active->left_child = new_node;
	  new_node->parent = active;
	  // Increase number of nodes in tree.
	  tree->number_of_nodes++;
	  // Check balance and rebalance.
	  upin(tree, new_node);
	  // Update the height of the tree.
	  tree->height = tree->root->height;
	  return 1;
	}

	// Continue traversal.
	active = active->left_child;
      }else if(key > active->key){
	// New node is expected to right of active.
	if(active->right_child == NULL){
	  // Insert to the right of active.
	  active->right_child = new_node;
	  new_node->parent = active;
	  // Increase number of nodes in tree.
	  tree->number_of_nodes++;
	  // Check balance and rebalance.
	  upin(tree, new_node);
	  // Update the height of the tree.
	  tree->height = tree->root->height;
	  return 1;
	}

	// Continue traversal.
	active = active->right_child; 
      }else{
	// Key already exists in tree. Insertion failure.
	return 0;
      }
    }
  }

  // This should be unreachable code. Error if reached.
  printf("Critical error occured while inserting a new node.\n");
  exit(2); // Exit with code 2. See Error index for details.
}

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
int key_delete(int key, AvlTree *tree){
  // Check arguments.
  assert(tree != NULL);

  // Pointer to the node to be deleted.
  Node *del_node = NULL;

  // Search for the key to be deleted.
  if(!search_by_key(key, tree, &del_node)){
    // The key was not found, return unsuccessful deletion.
    return 0;
  }

  if(del_node){
    // Pointer to the replacement node (for the deleted one).
    Node *repl = del_node->left_child;
    
    // If the replacement pointer is null, there was no left child.
    // Take the right one instead. If not, continue to iterate until
    // the correct replacement (the predecessor in the tree) is found.
    if(repl == NULL){
      repl = del_node->right_child;
    }else{
      // Iterate until predecessor is found.
      while(repl->right_child){
	repl = repl->right_child;
      }
    }

    // This points to the node from which we want to start the upout
    // procedure after deleting. Generally, this is the parent of the
    // actually unlinked node. So in case the replacement node is not
    // a direct child of the deletion node, this will point to the
    // parent of the replacement node. If it is a direct child, it will
    // point to the parent of the deletion node. If that is the root, we
    // let it point to NULL, and do not have to rebalance.
    Node *rebalance = NULL;
    if(repl){
      if(repl->parent != del_node) rebalance = repl->parent;

      // Give the replacement node the right child of the node to be
      // deleted. If the replacement is the right child of the node to
      // be deleted, skip this step.
      if(repl != del_node->right_child){
	repl->right_child = del_node->right_child;
	if(del_node->right_child) del_node->right_child->parent = repl;
      }

      // Give the parent of the replacement node its left child as a right child,
      // and adjust the left child of the replacement node to be the left child
      // of the deletion node.
      // If the parent of the replacement node is the deletion node itself, skip
      // this step.
      if(repl->parent != del_node){
	repl->parent->right_child = repl->left_child;
	if(repl->left_child) repl->left_child->parent = repl->parent;
	repl->left_child = del_node->left_child;
	del_node->left_child->parent = repl;
      }
    }else{
      if(!rebalance && del_node->parent) rebalance = del_node->parent;
    }
    
    // Point the parent of the deletion node to the replacement node.
    if(del_node->parent){
      if(del_node->key < del_node->parent->key){
	// Deletion node is a left child of its parent.
	del_node->parent->left_child = repl;
      }else{
	// Deletion node is a right child of its parent.
	del_node->parent->right_child = repl;
      }
      if(repl) repl->parent = del_node->parent;
    }else{
      // Handeling the deletion of the root.
      tree->root = repl;
      if(repl) repl->parent = NULL;
    }

    // Call the rebalance procedure from the rebalance node on (if one exists).
    if(rebalance){
      upout(tree, rebalance);
    }else{
      if(repl) upout(tree, repl);
    }

    // Update the tree height.
    if(tree->root){
      tree->height = tree->root->height;
    }else{
      tree->height = -1;
    }
    // Update the number of nodes in the tree.
    tree->number_of_nodes--;

    // Free the memory location and return.
    free(del_node);
    del_node = NULL;
    return 1;
  }

  // This should be unreachable code. Error if reached.
  printf("Critical error occured while deleting a node.\n");
  exit(2);
}

/*
 * Function: get_int_max
 * ---------------------
 * Description:
 * Simple helper function to determine the max of two
 * Integer numbers.
 *
 * Arguments: a - first value.
 *            b - second value.
 *
 * Returns: the maximum of the two.
 */
inline int get_int_max(int a, int b){
  return (a > b) ? a : b;
}
