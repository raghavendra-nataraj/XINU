#include <xinu.h>
syscall cond_signal(cont_t* cv){
if (lock == NULL)
		return SYSERR;

	if(*lock == 0)
		return SYSERR;
	else
		*lock = 0;
	
	return OK;
}
