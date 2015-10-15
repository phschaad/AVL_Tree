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
    if(p_bal >= 0){
      // Exit upin if the parent balance is 0.
      return;
    }else if(p_bal == -1){
      // Continue upin at the parent.
      upin(tree, parent);
    }else if(p_bal < -1){
      if(bal == -1){
	// Do a single right rotation.
	rotate_right(tree, parent);

	// TODO: update balance?
      }else if(bal == 1){
	// Do a double rotation (left, right).
	rotate_left(tree, parent->left_child);
	rotate_right(tree, parent);
	
	// TODO: update balance?
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
	
	// TODO: update balance?
      }else if(bal == -1){
	// Do a double rotation (right, left).
	rotate_right(tree, parent->right_child);
	rotate_left(tree, parent);

	// TODO: update balance?
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
  node->height = max(l_height, r_height) + 1;

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
  if(l_child->right_child) l_child->right_child->parent = node;
  l_child->right_child = node;
  node->parent = l_child;
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
  if(r_child->left_child) r_child->left_child->parent = node;
  r_child->left_child = node;
  node->parent = r_child;
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

    // Check balance and rebalance.
    upin(tree, new_node);
    return 1;
  }else{
    // Traverse the tree.
    // active keeps track of the current traversal "index".
    Node *active = tree->root;
    // Keeps track of the current traversal depth.
    int n_height = 0;
    
    while(1){
      if(key < active->key){
	// New node is expected to left of active.
	if(active->left_child == NULL){
	  // Insert to the left of active.
	  active->left_child = new_node;
	  new_node->parent = active;
	  n_height++; // Increment the new height.
	  // Check if hight needs to be updated, if yes do it.
	  tree->height = max(tree->height, n_height);
	  // Increase number of nodes in tree.
	  tree->number_of_nodes++;
	  
	  // Check balance and rebalance.
	  upin(tree, new_node);
	  return 1;
	}

	// Continue traversal.
	n_height++;
	active = active->left_child;
      }else if(key > active->key){
	// New node is expected to right of active.
	if(active->right_child == NULL){
	  // Insert to the right of active.
	  active->right_child = new_node;
	  new_node->parent = active;
	  n_height++; // Increment the new height.
	  // Check if hight needs to be updated, if yes, do it.
	  tree->height = max(tree->height, n_height);
	  // Increase number of nodes in tree.
	  tree->number_of_nodes++;
	  
	  // Check balance and rebalance.
	  upin(tree, new_node);
	  return 1;
	}

	// Continue traversal.
	n_height++;
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

  // TODO: Implement
}

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
int max(int a, int b){
  return (a > b) ? a : b;
}
