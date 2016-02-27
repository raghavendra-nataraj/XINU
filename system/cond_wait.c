#include <xinu.h>
syscall cond_wait(volatile cond_t* cv, mutex_t* lock){
	if (cv == NULL || lock == NULL)
		return SYSERR;
	mutex_unlock(lock);
	while (test_and_set(cv)) ;
	mutex_lock(lock);
	
	return OK;
}
