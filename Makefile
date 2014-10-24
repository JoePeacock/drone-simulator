make: shared.h drone.h drone.c main.c queue.h queue.c
	gcc shared.h queue.h queue.c drone.h drone.c main.c
