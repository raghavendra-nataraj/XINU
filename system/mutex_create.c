/* mutex_create.c - mutex_create */

#include <xinu.h>


/*------------------------------------------------------------------------
 *  mutex_create  -  Create a new lock and return the ID to the caller
 *------------------------------------------------------------------------
 */
syscall	mutex_create(
	  volatile mutex_t*	lock		/* Initial lock status	*/
	)
{
	if (lock == NULL)
		return SYSERR;
	*lock = 0;
	return OK;
}
