#include "xinu.h"
#include "future.h"
syscall future_set(future_t* f, int value){
	if(f.state == FUTURE_VALID)
	{
		pid32 pid = getpid();
		enqueue(f->set_queue,pid);
	}
	if(f.state == FUTURE_EMTPY || f.state == FUTURE_WAITING)
	{
		f.state = FUTURE_VALID;
		pid32 pid = dequeue(f->get_queue);
		resume(pid);
	}
	return 	OK;
}
