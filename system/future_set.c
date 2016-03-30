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
			enqueue(pid,f->set_queue);
		}
	}
	if(f->state == FUTURE_EMPTY || f->state == FUTURE_WAITING)
	{
		f->state = FUTURE_VALID;
		f->value = value;	
		pid32 pid;
		while((pid = dequeue(f->get_queue))!=EMPTY){
			resume(pid);
		}
	}
	return 	OK;
}
