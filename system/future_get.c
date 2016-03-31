#include <xinu.h>
#include <future.h>

syscall future_get(future_t* f, int* value){
	if(f->state == FUTURE_EMPTY || f->state == FUTURE_WAITING){
		pid32 pid = getpid();
		f->state = FUTURE_WAITING;
		//printf("get enque = %d\n",pid);
		pid = enqueue(pid,f->get_queue);
		suspend(pid);
	}
	
	if(f->state == FUTURE_VALID){
		pid32 pid;
		if(f->mode == FUTURE_QUEUE){
			if((pid = dequeue(f->set_queue))!=EMPTY){
				//printf("get deque = %d\n",pid);
				f->state = FUTURE_WAITING;
				resume(pid);
			}else{
				f->state = FUTURE_WAITING;
			}
		}
		if(isempty(f->get_queue))
			f->state = FUTURE_EMPTY;
		*value = f->value;
	}	
	return OK;	
}
