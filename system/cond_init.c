#include <xinu.h>
syscall cond_init(volatile cond_t* lock){
	if (lock == NULL)
		return SYSERR;
	*lock = 1;
	return OK;
}
