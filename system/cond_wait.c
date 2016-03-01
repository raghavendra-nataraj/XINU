#include <xinu.h>
syscall cond_wait(volatile cond_t* cv,volatile  mutex_t* lock){
	if (cv == NULL || lock == NULL)
		return SYSERR;
	mutex_unlock(lock);
	while (test_and_set(cv)) ;
	//resched();
	mutex_lock(lock);
	
	return OK;
}
