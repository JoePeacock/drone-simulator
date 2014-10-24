#include "drone.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define TAKEOFF_TIME 3
#define QUEUE_SLEEP 1

Drone *InitDrone(const char *name, const char *package, const int x, const int y, struct Queue *q, int g[][10]) {
  Drone *d = (Drone *) malloc(sizeof(Drone));
  d->package_id = malloc(sizeof(strlen(package)));
  d->drone_id = malloc(sizeof(strlen(name)));
  strcpy(d->drone_id, name);
  strcpy(d->package_id, package);
  d->d_x = x;
  d->d_y = y;
  d->c_x = 0;
  d->c_y = 0;
  d->q = q;
  d->grid = g;
  set_drone_state(d, READY);
  return d;
}

char *get_drone_state(Drone *drone) {
  switch(drone->current_state) {
    case READY: return "Ready.";
    case TAKEOFF_QUEUE: return "Waiting to take off...";
    case TAKING_OFF: return "Taking off.";
    case IN_FLIGHT: return "In transit.";
    case LANDING_QUEUE: return "Waiting to land...";
    case LANDING: return "Landing.";
    case DONE: return "Package Delivered.";
  }
}

void set_drone_state(Drone *drone, enum STATE state) {
  drone->current_state = state;
  printf("%s: %s \n", drone->drone_id, get_drone_state(drone));
  return;
}

void *StartDrone(void *vd) {
  Drone *d = vd;
  Enqueue(d->q, d);
  set_drone_state(d, TAKEOFF_QUEUE);
  TakeOff(d);
  return 0;
}

void TakeOff(Drone *d) {
  Drone *e = Peek(d->q);
  while (strcmp(d->drone_id, e->drone_id) != 0) {
    printf("%s: %s \n", d->drone_id, get_drone_state(d));
    e = Peek(d->q);
    sleep(QUEUE_SLEEP);
  }
  set_drone_state(d, TAKING_OFF);
  int i = TAKEOFF_TIME;
  while(i > 0) {
    printf("%s: %s - %d \n", d->drone_id, get_drone_state(d), i);
    i--;
    sleep(1);
  }
  Dequeue(d->q);
  set_drone_state(d, IN_FLIGHT);
  Fly(d);
}