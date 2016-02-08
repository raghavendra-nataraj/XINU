/* xsh_process_ring.c - xsh_process_ring*/

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <process_ring.h>
void ring_process(int);
sid32 lock;
int endProcess = 0;
int numberOfRounds;
shellcmd xsh_process_ring(int32 args,char *argv[]) {
	int i;
	numberOfRounds = 4;
	if (args == 2) {
		numberOfRounds = atoi(argv[1]);
	}
	if (args == 2 && strncmp(argv[1], "--help", 7) == 0) {
		printf("Usage: %s <string>\n\n ", argv[0]);
		printf("Description:\n");
		printf("Prints additional string\n");
		return 0;
	}
	endProcess = 0;
	lock = semcreate(0);
	for(i=0;i< NUM_PROCESSES;i++)
	{
		resume(create(ring_process,1024,20,"i",1,i));
	}
	signal(lock);
	return 0;
}
