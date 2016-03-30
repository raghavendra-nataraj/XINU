#include <xinu.h>
#include <future.h>

syscall future_get(future_t* f, int* value){
	if(f->state == FUTURE_EMPTY || f->state == FUTURE_WAITING){
		pid32 pid = getpid();
		f->state = FUTURE_WAITING;
		pid = enqueue(pid,f->get_queue);
		suspend(pid);
	}
	
	if(f->state == FUTURE_VALID){
		if(isempty(f->get_queue))
			f->state = FUTURE_EMPTY;
		*value = f->value;
	}	
	return OK;	
}
