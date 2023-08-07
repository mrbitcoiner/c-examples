#ifndef QUEUE_H
#define QUEUE_H

typedef struct q_node q_node;
typedef struct queue queue;

struct q_node {
  void *value;
  struct q_node *next;
};

struct queue {
  int count;
  q_node *head;
  q_node *tail;
};

queue q_init(void);
queue *q_enqueue(queue *q, q_node *node);
q_node *q_dequeue(queue *q);

#endif // !QUEUE_H
