/* mutex_unlock.c - mutex_unlock */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  mutex_unlock  -  lets current process to release the lock
 *------------------------------------------------------------------------
 */
syscall	mutex_lock(
	  mutex_t*	lock		/* Pointer to lock to be released*/
	)
{
	if (lock == NULL)
		return SYSERR;

	if(*lock == 0)
		return SYSERR;
	else
		*lock = 0;
	
	return OK;
}
