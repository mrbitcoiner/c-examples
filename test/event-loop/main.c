#include <stdio.h>
#include "queue.h"
#include "event_loop.h"

state_machine s1(state_machine machine);
state_machine s2(state_machine machine);
state_machine s3(state_machine machine);

static event_loop *runtime_global = NULL;

state_machine s1(state_machine machine){
  machine.transition_fn = &s2;
  machine.nullable_value += 1;
  printf("Machine %ld at state %zd\n", machine.id, (size_t)machine.nullable_value);
  return machine;
}

state_machine s2(state_machine machine){
  machine.transition_fn = &s3;
  machine.nullable_value += 1;
  printf("Machine %ld at state %zd\n", machine.id, (size_t)machine.nullable_value);
  return machine;
}

state_machine s3(state_machine machine){
  machine.transition_fn = NULL;
  machine.nullable_value += 1;
  machine.state = DONE;
  printf("Machine %ld at state %zd\n", machine.id, (size_t)machine.nullable_value);
  return machine;
}

int main(void) {
  event_loop runtime = event_loop_new();
  runtime_global = &runtime;

  state_machine m1 = {1, NULL, AWAITING, &s1};
  state_machine m2 = {2, NULL, AWAITING, &s1};
  state_machine m3 = {3, NULL, AWAITING, &s1};

  event_loop_schedule(&runtime, &m1);
  event_loop_schedule(&runtime, &m2);
  event_loop_schedule(&runtime, &m3);
  event_loop_start(&runtime);
  return 0;
}
