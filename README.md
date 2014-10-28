drone-simulator
===============

A C program that simulates multiple drones flying with pthreads.

### Running

First you need to setup the input file which is simply a text file with the following format:

```
int(number of drones)
name package x_coord,y_coord
name2 package2 x_coord,y_coord
```
The x and y coordinates may not exceed 10, otherwise the drone will fail to fly. The grid used is 10x10.

Name this file ``` input.txt ```. An example input is provided.

##### Run the script

Simply

```
$ bash run.sh
```

to start the simulation.

The outputs are printed to output.txt

### Design

Included is the design_docs directory which containts the FSM and State Table.

##### Software Design

The software is designed with a single queue, a 10x10 two dimensional array, pthreads and a drone struct.

Each drone has its own struct associated with it, and is populated by the input file with its destination, name, and package. At this point this struct is passed into a new thread via the StartDrone function.

After the thread begins it is added to the take-off queue. Once added it waits until it is first and line and then takes off (this takes 3 seconds). 

One the drone "takes off" the drone is on the grid starting at (0,0). From here the drone navigates horizontally and then veritcally to its destination before landing. The drone moves at a speed of one square per second, being (0,0) to (1,0) taking 1 second.
