#include <xinu.h>
syscall cond_signal(volatile cond_t* lock){
if (lock == NULL)
		return SYSERR;

	*lock = 0;
	
	return OK;
}
