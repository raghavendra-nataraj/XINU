/* xsh_process_ring.c - xsh_process_ring*/

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <process_ring.h>
void ring_process(int);
volatile int count = 0;
int numberOfRounds;
shellcmd xsh_process_ring(int32 args,char *argv[]) {
	int i;
	numberOfRounds = 4;
	if (args == 2) {
		numberOfRounds = atoi(argv[1]);
	}
	if (args == 2 && strncmp(argv[1], "--help", 7) == 0) {
		printf("Usage: %s <rounds>\n\n ", argv[0]);
		return 0;
	}
	inbox[0] = count = NUM_PROCESSES * numberOfRounds;
	for(i=0;i< NUM_PROCESSES;i++)
	{
		resume(create(ring_process,1024,20,"i",1,i));
	}
	return 0;
}
