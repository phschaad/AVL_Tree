#include "avl_core.h"
#include "avl_visualizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_in_range(int min, int max){
  return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int main(int argc, char **argv){
  AvlTree *tree = make_tree_empty();
  
  srand(time(NULL));
  // 17
  for(int i = 0; i < 30; i++){
    int r = rand_in_range(1, 999);
    key_insert_new(r, tree);
  }
  
  printf("Preorder traversal: ");
  traverse_preorder_console(tree->root);
  printf("\nInorder traversal: ");
  traverse_inorder_console(tree->root);
  printf("\nNumber of nodes: %d\n", tree->number_of_nodes);
  printf("Number of levels: %d\n", tree->height + 1);
  visualize(tree);
  
  return 0;
}
