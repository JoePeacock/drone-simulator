#include "queue.h"

// Lets define our drone states as an enum for easy checking and setting. 
enum STATE 
{
  READY, 
  TAKEOFF_QUEUE, 
  TAKING_OFF, 
  IN_FLIGHT, 
  LANDING_QUEUE, 
  LANDING, 
  DONE,
  FAILED
};

typedef struct {

  char *drone_id;
  char *package_id;

  int d_x;
  int d_y;

  int c_x;
  int c_y;

  int (*grid)[10];
  struct Queue *q;

  enum STATE current_state;

} Drone;

// Initializes a drone with an id number and sets that to the 
// struct member drone_id. Returns a pointer to a Drone struct.
Drone *InitDrone(const char *name, const char *package, const int x, const int y, struct Queue *q, int (*g)[10]);

// Returns a physical string of the drone's state taken from 
// the int state; struct member and matching it to an array of strings
// to state names 
char *get_drone_state(Drone *drone);

// Sets the drone state to an integer. This is a helper function and should 
// only be called by action function ie(TakeOff, or Land). Do not call directly!
void set_drone_state(Drone *drone, enum STATE state);

void *StartDrone(void *vd);

void TakeOff(Drone *d);

void Fly(Drone *d);
