#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(void){
  queue queue = q_init();

  const int n_nodes = 10;

  for (int i = 0; i < n_nodes; i++){
    q_node *node = malloc(sizeof(q_node));
    node->value = NULL;
    node->next = NULL;
    int *value = malloc(sizeof(int));
    *value = i;
    node->value = value;
    q_enqueue(&queue, node);
    printf("Enqueued: %d\n", *(int *) node->value);
  }

  for(q_node *node; (node = q_dequeue(&queue)) ; ){
    printf("Dequeued: %d\n", *(int *) node->value);
    free(node->value);
    node->value = NULL;
    free(node);
    node = NULL;
  }

  for (int i = 0; i < n_nodes; i++){
    q_node *node = malloc(sizeof(q_node));
    node->value = NULL;
    node->next = NULL;
    int *value = malloc(sizeof(int));
    *value = i;
    node->value = value;
    q_enqueue(&queue, node);
    printf("Enqueued: %d\n", *(int *) node->value);
  }

  for(q_node *node; (node = q_dequeue(&queue)) ; ){
    printf("Dequeued: %d\n", *(int *) node->value);
    free(node->value);
    node->value = NULL;
    free(node);
    node = NULL;
  }

  return 0;
}
