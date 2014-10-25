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
    case LANDING: return "Landing.";
    case FLIGHT_EVADING: return "Evading an immenent collision!";
    case ARRIVED: return "Drone has arrived at its destination.";
    case DELIVERING: return "Delivering the package!";
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
  while (1) {
    switch(d->current_state) {
      case READY: TakeOff(d);
      case IN_FLIGHT: Fly(d);
      case ARRIVED: LandDrone(d);
      case DELIVERING: DeliverPackage(d);
      case DONE: return 0;
      case FAILED: return 0;
      case TAKING_OFF: ;
      case TAKEOFF_QUEUE: ;
      case FLIGHT_EVADING: ;
      case LANDING: ;
    }
  }
  return 0;
}

void TakeOff(Drone *d) {
  Enqueue(d->q, d);
  set_drone_state(d, TAKEOFF_QUEUE);
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
}

/*
 * Function:    move_drone
 *
 * Oh boy this is a fun function. Hacked together way to move vertically or
 * horizontally. Done via passing a pointer to the drone's current position and 
 * updating that value (pointer to the drone).
 *
 * Drone *d:           The drone you want to update.
 * signed int partiy:  The difference in coordinates. Gets you positive or neg difference.
 * signed int *value:  The pointer to the value on the drone, either x or y.    
 * 
 */
void move_drone(Drone *d, signed int parity, signed int *value) {

  int temp_x;
  int temp_y;
  memcpy(&temp_x, &d->c_x, sizeof(d->c_x));
  memcpy(&temp_y, &d->c_y, sizeof(d->c_y));

  // As we move along, we need to continously occupy and free spaces.
  if(parity > 0) {
    *value+=1;
  } else if (parity < 0) {
    *value-=1;
  }

  while (d->grid[d->c_x][d->c_y] == OCCUPIED) {
    set_drone_state(d, FLIGHT_EVADING);
    sleep(1);
  }

  set_drone_state(d, IN_FLIGHT);
  d->grid[d->c_x][d->c_y] = OCCUPIED;
  d->grid[temp_x][temp_y] = LEAVE;
  printf("%s: %s (%d, %d) \n", d->drone_id, get_drone_state(d), d->c_x, d->c_y);

}

/*
 * Function:    Fly
 *
 * Function called directly after TakeOff is completed to move the drone out of the
 * starting space and to its destination. This is done by first moving horizontally, 
 * then vertically. If the next spot is already occupied it switches to FLYING_EVADE, where it
 * it waits in its current position for 1 second and checks again.
 *
 * Drone *d:    The drone that you want to fly
 */
void Fly(Drone *d) {
  // First step is set our drone in the grid.
  d->grid[d->c_x][d->c_y] = OCCUPIED;
  if (d->d_x > GRID_X || d->d_y > GRID_Y) {
    printf("Coordinates are out of range! Failed to travel. Returning to base. \n");
    set_drone_state(d, FAILED);
    return;
  }
  // Ok next step is to calculate where the hell we have to go.
  // Our speed will be 1sps (square per second)
  signed int x_diff = d->d_x - d->c_x;
  signed int y_diff = d->d_y - d->c_y;
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
  set_drone_state(d, ARRIVED);
}

/*
 * Function:    LandDrone
 *
 * Simple function that removes the drone from the grid by landing. The Drone stays in the grid 
 * so long as the drone has not fully landed yet. 
 *
 * Drone *d:    The drone to land.
 */
void LandDrone(Drone *d) {
  set_drone_state(d, LANDING);
  // Landing timer
  int i = TAKEOFF_TIME;
  while(i > 0) {
    printf("%s: %s - %d \n", d->drone_id, get_drone_state(d), i);
    sleep(1);
    i--;
  }
  // Remove the drone from the grid. 
  d->grid[d->c_x][d->c_y] = LEAVE;
  set_drone_state(d, DELIVERING);
}

void DeliverPackage(Drone *d) {
  sleep(2);
  set_drone_state(d, DONE);
}
