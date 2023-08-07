#include "stdio.h"
#include "queue.h"

// Initializes the queue
// Arguments: void
// Return value: instance of queue
queue q_init(void){
  queue q;
  q.count = 0;
  q.head = NULL;
  q.tail = NULL;
  return q;
}

// Add a new node to the queue tail
// Arguments: 
//  1 - Pointer to the queue;
//  2 - Pointer to the node being enqueued;
// Return value: pointer to the queue
queue *q_enqueue(queue *q, q_node *node){
  // if there's no tail, just add the node to the tail and the head
  if (!q->tail){
    q->tail = node;
    q->head = node;
  }
  // if there's a tail, point the tail node to the new node
  //   and the new node becomes the new tail
  else {
    q->tail->next = node;
    q->tail = node;
  }
  // increment the counter
  q->count++;
  return q;
}


// Pull the node from the queue head
// Arguments:
//  1 - Pointer to the queue;
// Return value: 
//  On Success: void pointer to the node
//  On Failure: null pointer
q_node *q_dequeue(queue *q){
  q_node *node = NULL;
  // if there's no node return null
  if (!q->head) return NULL;
  // if the head node points to null, get the node value and set head and tail to null
  else if (!q->head->next){
    node = q->head;
    q->head = NULL;
    q->tail = NULL;
  }
  // if the head node doesn't point to null, get the node value and set the head to the next value
  else {
    node = q->head;
    q->head = q->head->next;
  }
  // decrement counter
  q->count --;
  return node;
}
