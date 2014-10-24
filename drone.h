// Lets define our drone states as an enum for easy checking and setting. 
enum STATE 
{
  READY, 
  TAKEOFF_QUEUE, 
  TAKING_OFF, 
  IN_FLIGHT, 
  LANDING_QUEUE, 
  LANDING, 
  DONE
};

typedef struct {

  char *drone_id;

  enum STATE current_state;
  int package_id;

  char *destination;
  int travel_time_s;

} Drone;

// Initializes a drone with an id number and sets that to the 
// struct member drone_id. Returns a pointer to a Drone struct.
Drone *InitDrone(const char* name);

// Returns a physical string of the drone's state taken from 
// the int state; struct member and matching it to an array of strings
// to state names 
char *get_drone_state(Drone *drone);

// Sets the drone state to an integer. This is a helper function and should 
// only be called by action function ie(TakeOff, or Land). Do not call directly!
void set_drone_state(Drone *drone, enum STATE state);

// Sets the distance a drone will be travelling in seconds.
void set_travel_time(Drone *drone);
