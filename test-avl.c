#include "avl_core.h"

int main(int argc, char **argv){
  AvlTree *tree = make_tree_empty();

  insert_node_key(3, tree);
  insert_node_key(5, tree);
  insert_node_key(6, tree);
  insert_node_key(1, tree);
  insert_node_key(2, tree);
  insert_node_key(9, tree);

  traverse_inorder_console(tree->root);
  printf("\nNumber of nodes: %d\n", tree->number_of_nodes);

  return 0;
}
