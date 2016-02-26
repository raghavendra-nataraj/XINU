/* mutex_create.c - mutex_create */

#include <xinu.h>


/*------------------------------------------------------------------------
 *  mutex_create  -  Create a new lock and return the ID to the caller
 *------------------------------------------------------------------------
 */
syscall	mutex_create(
	  mutex_t*	lock		/* Initial lock status	*/
	)
{
	if (lock == NULL)
		return SYSERR;
	if (test_and_set(lock)) {
		*lock = 0;
		return OK;
	}
}
