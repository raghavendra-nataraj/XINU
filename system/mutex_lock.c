/* mutex_lock.c - mutex_lock */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  mutex_lock  -  lets current process to accuire the lock
 *------------------------------------------------------------------------
 */
syscall	mutex_lock(
	 volatile  mutex_t*	lock		/* Pointer to lock to be held*/
	)
{
	if (lock == NULL)
		return SYSERR;

	while (test_and_set(lock)) ;
	
	return OK;
}
