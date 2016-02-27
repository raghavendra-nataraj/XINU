/* mutex_unlock.c - mutex_unlock */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  mutex_unlock  -  lets current process to release the lock
 *------------------------------------------------------------------------
 */
syscall	mutex_unlock(
	  volatile mutex_t*	lock		/* Pointer to lock to be released*/
	)
{
	if (lock == NULL)
		return SYSERR;

	*lock = 0;
	
	return OK;
}
