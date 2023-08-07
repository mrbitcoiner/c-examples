#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

typedef struct state_machine state_machine;
typedef enum sm_state sm_state;
typedef struct event_loop event_loop;

enum sm_state {
  // Will be polled again
  AWAITING,
  // Will be discarded
  DONE,
};

struct state_machine {
  long id;
  // Use this pointer as you want. I won't use it.
  // I won't free memory that I've not allocated
  void* nullable_value;
  sm_state state;
  // If the state is AWAITING, this function will be called
  state_machine (*transition_fn)(state_machine);
};

struct event_loop {
  queue event_queue;
};

event_loop event_loop_new(void);
void event_loop_schedule(event_loop *loop, state_machine *machine);
void event_loop_start(event_loop *loop);

#endif
