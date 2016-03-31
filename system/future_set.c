#include <xinu.h>
#include <future.h>

syscall future_set(future_t* f, int value){
	if(f->state == FUTURE_VALID)
	{
		if(f->mode == FUTURE_EXCLUSIVE || f->mode == FUTURE_SHARED ){
			printf("The mode is exclusive , Please change the mode\n");
			return SYSERR;
		}else{
			pid32 pid = getpid();
			//printf("set enque = %d\n",pid);
			enqueue(pid,f->set_queue);
			suspend(pid);
		}
	}
	if(f->state == FUTURE_EMPTY || f->state == FUTURE_WAITING)
	{
		if(isempty(f->get_queue)){
			pid32 pid = getpid();
			//printf("set self enque = %d\n",pid);
			enqueue(pid,f->set_queue);
			suspend(pid);
		}
		f->state = FUTURE_VALID;
		f->value = value;	
		pid32 pid;
		if(f->mode == FUTURE_QUEUE){
			if((pid = dequeue(f->get_queue))!=EMPTY){
				//printf("get deque = %d\n",pid);
				resume(pid);
			}
		}else{	
			while((pid = dequeue(f->get_queue))!=EMPTY){
				resume(pid);
			}
		}
		
	}
	return 	OK;
}
