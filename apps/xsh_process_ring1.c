#include <xinu.h>
#include <kernel.h>
#include <process_ring.h>
int inbox[NUM_PROCESSES];
void ring_process(int ring_element){
	int round = 0;
	//int inbox[NUM_PROCESSES];
	inbox[0] = NUM_PROCESSES * numberOfRounds;
	while(1){
		wait(lock);
		if(inbox[ring_element]<=0 || 1 == endProcess){
			if(inbox[ring_element]<=0) kprintf("ZERO!\n");
			endProcess = 1;
			signal(lock);
			return;
		}
		
		kprintf("Ring Element %d : Round %d : Value : %d\n",ring_element,round,inbox[ring_element]);
		inbox[(ring_element+1)%NUM_PROCESSES] = inbox[ring_element]-1;
		round++;
		signal(lock);
	}
}
