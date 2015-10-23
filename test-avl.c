#include "avl_core.h"
#include "avl_visualizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define N_INSERT 1000 // The number of values to insert.
#define N_REMOVE 900 // The numver of values to delete. 

int has(AvlTree *tree, int key){
  Node *node = NULL;
  return search_by_key(key, tree, &node);
}

/**
 * @brief Generate a random number in a given range.
 * @param min - The lower bound of the range.
 * @param max - The upper bound of the range.
 * @return A random number in the given range.
 */
int rand_in_range(int min, int max){
  return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

/**
 * @brief Recursively recalculate the height of every node.
 * @param node - The currently looked at node.
 * @return The height of the node currently looked at.
 */
int rec_height(Node *node){
  if(!node) return -1;
  node->height = get_int_max(
			     rec_height(node->left_child),
			     rec_height(node->right_child)) + 1;
  return node->height;
}

/**
 * @brief Recursively check if the tree holds the avl property.
 * For this to give the correct result, the height of every node
 * has to be correct in advance. It is recommended to run rec_height
 * on the root, before executing the check_avl_property function.
 * @param node - The currently looked at node. 
 * @return 1 - If the avl property holds, 0 - otherwise.
 */
int check_avl_property(Node *node){
  if(!node) return 1;
  int l_height = -1;
  int r_height = -1;
  if(node->left_child) l_height = node->left_child->height;
  if(node->right_child) r_height = node->right_child->height;
  int bal = r_height - l_height;
  int is_avl = ((bal >= -1) && (bal <= 1)) ? 1 : 0;
  return is_avl
    && check_avl_property(node->left_child)
    && check_avl_property(node->right_child);
}

int main(int argc, char **argv){
  // Create an empty avl tree.
  AvlTree *tree = make_tree_empty();

  int insert_values[N_INSERT];
  int delete_values[N_REMOVE];
  
  srand(time(NULL));
  for(int i = 0; i < N_INSERT; i++){
    int r = rand_in_range(1, 9999999);
    insert_values[i] = r;
    key_insert_new(r, tree);
  }
  
  /* printf("Inorder traversal: "); */
  /* traverse_inorder_console(tree->root); */
  printf("\nNumber of nodes: %d\n", tree->number_of_nodes);
  printf("Number of levels: %d\n", tree->height + 1);
  /* printf("Visual representation:\n"); */
  /* visualize(tree); */

  // Recalculate the heights and check avl property.
  rec_height(tree->root);
  if(check_avl_property(tree->root)){
    printf("AVL property satisfied.\n");
  }else{
    printf("AVL property violated.\n");
  }

  for(int i = 0; i < N_INSERT; i++){
    if(!has(tree, insert_values[i])){
      printf("Did not find key %d despite having added it!\n",
  	     insert_values[i]);
    }
  }
  
  for(int i = 0; i < N_REMOVE; i++){
    int r = rand_in_range(0, N_INSERT - 1);
    delete_values[i] = insert_values[r];
    key_delete(delete_values[i], tree);
  }

  for(int i = 0; i < N_REMOVE; i++){
    if(has(tree, delete_values[i])){
      printf("Found key %d in tree, despite having removed it!\n",
  	     delete_values[i]);
    }
  }
  
  /* printf("Inorder traversal: "); */
  /* traverse_inorder_console(tree->root); */
  printf("\nNumber of nodes: %d\n", tree->number_of_nodes);
  printf("Number of levels: %d\n", tree->height + 1);
  /* printf("Visual representation:\n"); */
  /* visualize(tree); */

  // Recalculate the heights and check avl property.
  rec_height(tree->root);
  if(check_avl_property(tree->root)){
    printf("AVL property satisfied.\n");
  }else{
    printf("AVL property violated.\n");
  }

  /*
   * --------------
   * -- Cleanup. --
   * --------------
   */
  
  // Remove all nodes from the tree.
  for(int i = 0; i < N_INSERT; i++){
    key_delete(insert_values[i], tree);
  }
  
  // Remove the tree.
  free(tree);
  tree = NULL;
  
  return 0;
}
