#include <xinu.h>
syscall cond_wait(cont_t* cv, mutex_t* lock){
	if (lock == NULL)
		return SYSERR;
	mutex_unlock(lock)
	while (test_and_set(lock)) ;
	mutex_lock(lock);
	
	return OK;
}
