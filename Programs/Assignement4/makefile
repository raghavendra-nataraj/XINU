CC = gcc
OBJ = ipc_bench.c follower.c leader.c helper.c
all: ipc_bench

ipc_bench: $(OBJ)
	$(CC) -o ipc_bench $(OBJ) -lpthread -lrt

%o: %c
	$(CC) $< -o $@ -lpthread -lrt

clean:
	rm *.o ipc_bench 
	
