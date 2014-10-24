#include <stdlib.h>
#include <stdio.h>
#include "drone.h"
#include <time.h>
#include <string.h>

Drone *InitDrone(const char* name) {
  Drone *d = (Drone *) malloc(sizeof(Drone));
  d->drone_id = malloc(sizeof(strlen(name)));
  strcpy(d->drone_id,name);

  // char* my_name = malloc(sizeof(strlen(name)));
  // strcpy(my_name,name);
  // d->drone_id = my_name;
  
  d->current_state = READY;
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
  return;
}

void set_travel_time(Drone *drone) {
  srand(time(0));
  int distance_time = rand() % 50;
  drone->travel_time_s = distance_time;
  return;
}
