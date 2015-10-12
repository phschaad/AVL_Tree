/* Basic AVL-Tree implementation - Core module */
/*
 * Author: Philipp Schaad
 * Creation Date: 011015 
 */

#include "avl_core.h"

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
  // Allocate space for the new tree.
  AvlTree *tree = (AvlTree *)malloc(sizeof(AvlTree));
  if(tree == NULL){
    // Memory allocation failed, report.
    printf("Memory allocation failed while generating a new tree from a node.\n");
    return NULL;
  }
  if(node == NULL){
    // NULL argument, report illegal state.
    printf("Illegal argument state in make_tree_from_node.\n");
    return NULL; 
  }

  tree->root = NULL;
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
    // Failed memory allocation. Report.
    printf("Memory allocation failed in empty tree genertaion.\n");
    return NULL;
  }
  new_tree->root = NULL;
  new_tree->height = -1;
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
    // Check if memory allocation succeeded.
    printf("Memory allocation failed while generating a new empty node.\n");
    return NULL;
  }
  new_node->data = NULL;
  new_node->key = key;
  new_node->left_child = NULL;
  new_node->right_child = NULL;
  new_node->balance = 0;
  return new_node;
}

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
int search_node(int key, AvlTree *tree, Node **node){
  // Check if the tree is empty.
  if(tree->root == NULL){
    // Return a NULL-pointer on the node, and falsy.
    *node = NULL;
    return 0;
  }

  // Start traversing the tree.
  *node = tree->root;
  while(true){
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

  // Safety fall-thru. This should not return.
  return -1; // Fatal error if returned.
}

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
int insert_node_key(int key, AvlTree *tree){
  // Pointer to the insertion-location.
  Node *parent = NULL;
  // Search for the node, resp. the parent.
  int response = search_node(key, tree, &parent);

  if(response == 0){
    Node *new_node = make_node_empty(key);
    if(new_node == NULL){
      // Error in allocation.
      return -1;
    }

    if(parent == NULL){
      // The tree has no root yet, make it the new node.
      tree->root = new_node;
      tree->number_of_nodes++;
      return 1;
    }else if(key < parent->key){
      if(parent->left_child){
	printf("Tried insertion with non-empty child position in parent.\n");
	return -1;
      }
      parent->left_child = new_node;
      tree->number_of_nodes++;
      return 1;
    }else if(key > parent->key){
      if(parent->right_child){
	printf("Tried insertion with non-empty child position in parent.\n");
	return -1;
      }
      parent->right_child = new_node;
      tree->number_of_nodes++;
      return 1;
    }
    // This should not return.
    return -1;
  }else if(response == -1){
    // Error in search, propagate it.
    return -1;
  }else{
    // Key already in tree, return 0.
    return 0;
  }

  // Safety fall-thru. This should never return.
  return -1; // Fatal error if returned.
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
