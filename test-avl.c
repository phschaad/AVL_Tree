#include "avl_core.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_in_range(int min, int max){
  return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int main(int argc, char **argv){
  AvlTree *tree = make_tree_empty();
  
  /* srand(time(NULL)); */
  /* for(int i = 0; i < 50; i++){ */
  /*   int r = rand_in_range(1, 150); */
  /*   key_insert_new(r, tree); */
  /* } */
  
  key_insert_new(3, tree);
  key_insert_new(5, tree);
  key_insert_new(6, tree);
  key_insert_new(1, tree);
  key_insert_new(2, tree);
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
