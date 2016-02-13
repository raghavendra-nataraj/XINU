#include <xinu.h>
#include <kernel.h>
#include <process_ring.h>

volatile int inbox[NUM_PROCESSES];

void ring_process(int ring_element){
	int round = 0;
	//int count = numberOfRounds * NUM_PROCESSES;
	while(1){
		// proper
		if(count%NUM_PROCESSES == (NUM_PROCESSES-ring_element)%NUM_PROCESSES){
			//count = inbox[ring_element];	
			kprintf("Ring Element %d : Round %d : Value : %d\n",ring_element,round++,inbox[ring_element]);		
			inbox[(ring_element+1)%NUM_PROCESSES]=--count;

			if(count<0) return;		
		}
	
		// wrong order
		/*if(count%NUM_PROCESSES == (NUM_PROCESSES-ring_element)%NUM_PROCESSES){
			//count = inbox[ring_element];	
			inbox[(ring_element+1)%NUM_PROCESSES]=--count;
			kprintf("Ring Element %d : Round %d : Value : %d\n",ring_element,round++,inbox[ring_element]);		
	

			if(count<0) return;		
		}*/

		//Infinite
		/*if(inbox[ring_element]%NUM_PROCESSES == (NUM_PROCESSES-ring_element)%NUM_PROCESSES){
			count = inbox[ring_element];	
			kprintf("Ring Element %d : Round %d : Value : %d\n",ring_element,round++,inbox[ring_element]);		
			inbox[(ring_element+1)%NUM_PROCESSES]=count-1;

			if(count<0) return;		
		}*/

		// hang internal count
		/*if(count%NUM_PROCESSES == (NUM_PROCESSES-ring_element)%NUM_PROCESSES){
			//count = inbox[ring_element];	
			inbox[(ring_element+1)%NUM_PROCESSES]=count-1;
			kprintf("Ring Element %d : Round %d : Value : %d\n",ring_element,round++,inbox[ring_element]);		
			count = count-1;
			if(count<0) return;		
		}*/	
		//printf("Count = %d\n",count);		
		if(count<0) return;		
	}
}
