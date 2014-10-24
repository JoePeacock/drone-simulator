#include "drone.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

Drone *InitDrone(const char *name, const char *package, const int x, const int y, struct Queue *q, int g[][10]) {
  Drone *d = (Drone *) malloc(sizeof(Drone));
  d->package_id = malloc(sizeof(strlen(package)));
  d->drone_id = malloc(sizeof(strlen(name)));
  strcpy(d->drone_id, name);
  strcpy(d->package_id, package);
  d->d_x = x;
  d->d_y = y;
  d->c_x = START_X;
  d->c_y = START_Y;
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
    case FAILED: return "Missions Failed.";
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

void move_drone(Drone *d, signed int parity, signed int *value) {
  d->grid[d->c_x][d->c_y] = LEAVE;
  if(parity > 0) {
    *value+=1;
    d->grid[d->c_x][d->c_y] = OCCUPIED;
  } else if (parity < 0) {
    *value-=1;
    d->grid[d->c_x][d->c_y] = OCCUPIED;
  }
  printf("%s: %s (%d, %d) \n", d->drone_id, get_drone_state(d), d->c_x, d->c_y);
}

void Fly(Drone *d) {

  // First step is set our drone in the grid.
  d->grid[d->c_x][d->c_y] = OCCUPIED;

  if (d->d_x > GRID_X || d->d_y > GRID_Y) {
    printf("Coordinates are out of range! Failed to travel. Returning to base. \n");
    set_drone_state(d, FAILED);
    return;
  }

  // Ok next step is to calculate where the hell we have to go.
  // Lets design this real simple. First move laterally until at the correct columns,
  // then move horizontally to your destination. Our speed will be 1sps (square per second)
  signed int x_diff = d->d_x - d->c_x;
  signed int y_diff = d->d_y - d->c_y;

  // As we move along, we need to continously occupy and free spaces.
  // First Horizontal
  while (d->c_x != d->d_x) {
    move_drone(d, x_diff, &d->c_x);
    sleep(SPS_SPEED);
  }

  // Now Verticle
  while(d->c_y != d->d_y) {
    move_drone(d, y_diff, &d->c_y);
    sleep(SPS_SPEED);
  }
  
  // Should have arrived at our destination by now. Hopefully..
  printf("%s: ARRIVED!! \n", d->drone_id);
}