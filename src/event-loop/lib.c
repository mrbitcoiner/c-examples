#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"
#include "event_loop.h"

// Frees the queue node and the state machine
static void free_state_machine_node(q_node *machine_node){
  free(machine_node->value);
  machine_node->value = NULL;
  free(machine_node);
}

// Will block forever
void event_loop_start(event_loop *loop){
  queue q = loop->event_queue;
  for (;;) {
    q_node *node = q_dequeue(&q);
    if (!node){ printf("Empty queue\n"); usleep(1000000); continue; };
    state_machine *machine = node->value;
    if (machine->state == DONE) { free_state_machine_node(node); continue; };
    state_machine after_transition = machine->transition_fn(*machine);
    *machine = after_transition;
    node->value = machine;
    node->next = NULL;
    q_enqueue(&loop->event_queue, node);
  }
}

// Schedule new state machine
void event_loop_schedule(event_loop *loop, state_machine *machine){
  state_machine *state_machine_heap = malloc(sizeof(state_machine));
  *state_machine_heap = *machine;
  q_node *q_node_heap = malloc(sizeof(q_node));
  q_node q_node = {state_machine_heap, NULL};
  *q_node_heap = q_node;
  q_enqueue(&loop->event_queue, q_node_heap);
}

// Create the event loop instance
event_loop event_loop_new(void){
  event_loop ev_loop = {q_init()};
  return ev_loop;
}

