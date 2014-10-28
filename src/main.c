#include "drone.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define true 1
#define false 0

int main(int argc,char *argv[]) {

  if (argc != 2) {

    printf("Usage: %s drone_schedule.file", argv[0]);

  } else {

    // Instantiate our global variables.
    // That is an NxN grid for our drone space and a queue for taking off
    // These are stored in "shared.h".

    int grid[GRID_X][GRID_Y];
    int i, j;
    for (i = 0; i < GRID_X; i++) {
      for (j = 0; j < GRID_Y; j++) {
        grid[i][j] = 0;
      }
    }

    struct Queue *queue = NewQueue();

    // Now that we have that created, lets read our drone file..
    FILE *fp;
    if ((fp = fopen(argv[1], "r")) == 0) {
      printf("Could not open file %s \n", argv[1]);
      return 0;
    }

    int number_of_drones;
    fscanf(fp, "%d", &number_of_drones);

    char drone_name[10], drone_package_id[10];
    int x, y;

    pthread_t threads[number_of_drones];

    // Here we read in each drone declared on a new line, and send them off!
    int rc;
    int thread_count = 0;
    while(fscanf(fp, "%s %s %d,%d\n", drone_name, drone_package_id, &x, &y) == 4) {
      Drone *d = InitDrone(drone_name, drone_package_id, x, y, queue, grid);
      rc = pthread_create(&threads[thread_count], NULL, StartDrone, d);
      if (rc) {
        printf("Error creating thread!");
        return 0;
      }
      thread_count++;
    }
    // Cleanup!
    fclose(fp);
    pthread_exit(NULL);
  }
}
