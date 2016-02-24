/* tas_unlock.c - tas_unlock */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  tas_unlock -  Releases the lock if held by the current process
 *------------------------------------------------------------------------
 */

syscall tas_unlock(
	  int32*	lock		/* Pointer to lock to be released*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/

	mask = disable();
	if (lock == NULL) {
		restore(mask);
		return SYSERR;
	}

	if (*lock == 0) {
		restore(mask);
		return SYSERR;
	}

	*lock = 0;		
	restore(mask);
	return OK;
}
