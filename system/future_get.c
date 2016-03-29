#include "xinu.h"
#include "future.h"

syscall future_get(future_t* f, int* value){
	if(f->state == FUTURE_EMPTY || f->state == FUTURE_WAITING){
		pid32 pid = getpid();
		enqueue(f->set_queue,pid);
		suspend(pid);
	}
	
	if(f->state == FUTURE_VALID){
		f->state = FUTURE_EMPTY;
		*value = f->value;
	}		
}
