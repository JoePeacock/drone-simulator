#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0

int main(int argc,char *argv[]) {

  if (argc != 2) {
    printf("Usage: %s filename", argv[0]);
  } else {
    bool start_drone = true;
    struct Queue *t = NewQueue();

    while(start_drone) {
      char input[2];
      printf("%s", "Would you like to start a drone? (y or n): "); 
      scanf("%c", input);
      getchar();

      if (strncmp(input, "y", 100)  == 0) {
        char name[100];
        printf("%s", "Please enter an id for your drone ie(AB107): ");     
        scanf("%s", name);
        getchar();

        Drone *d = InitDrone(name);
        set_travel_time(d);
        Add(t, d);
        PrintQueue(t);

      } else {
        start_drone = false;
      }
    }  
  }
}
