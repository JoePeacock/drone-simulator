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
