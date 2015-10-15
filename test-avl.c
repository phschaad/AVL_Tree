#include "avl_core.h"

#include <stdio.h>

int main(int argc, char **argv){
  AvlTree *tree = make_tree_empty();

  /* key_insert_new(1, tree); */
  /* key_insert_new(3, tree); */
  /* key_insert_new(2, tree); */
  
  /* key_insert_new(3, tree); */
  /* key_insert_new(5, tree); */
  /* key_insert_new(6, tree); */
  
  /* key_insert_new(6, tree); */
  /* key_insert_new(5, tree); */
  /* key_insert_new(3, tree); */
  /* key_insert_new(1, tree); */
  /* key_insert_new(2, tree); */
  
  key_insert_new(3, tree);
  key_insert_new(5, tree);
  key_insert_new(6, tree);
  key_insert_new(1, tree);

  printf("Preorder traversal: ");
  traverse_preorder_console(tree->root);
  printf("\nInorder traversal: ");
  traverse_inorder_console(tree->root);
  printf("\nNumber of nodes: %d\n", tree->number_of_nodes);
  printf("Number of levels: %d\n", tree->height + 1);
  visualize(tree);
  

  key_insert_new(2, tree);

  printf("Preorder traversal: ");
  traverse_preorder_console(tree->root);
  printf("\nInorder traversal: ");
  traverse_inorder_console(tree->root);
  printf("\nNumber of nodes: %d\n", tree->number_of_nodes);
  printf("Number of levels: %d\n", tree->height + 1);
  visualize(tree);
  
  
  key_insert_new(9, tree);

  printf("Preorder traversal: ");
  traverse_preorder_console(tree->root);
  printf("\nInorder traversal: ");
  traverse_inorder_console(tree->root);
  printf("\nNumber of nodes: %d\n", tree->number_of_nodes);
  printf("Number of levels: %d\n", tree->height + 1);
  visualize(tree);
  
  return 0;
}
