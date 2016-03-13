CC = gcc
OBJ = ipc_bench.o follower.o leader.o helper.o

all: ipc_bench

ipc_bench: $(OBJ)
	$(CC) -o ipc_bench $(OBJ) -lpthread

%o: %c
	$(CC) $< -o $@

clean:
	rm *.o ipc_bench 
	
