/* tas_lock.c - tas_lock */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  tas_lock  -  Cause current process to test and set lock
 *------------------------------------------------------------------------
 */
int32	tas_lock(
	  int32*	lock		/* Pointer to lock to be held*/
	)
{
	intmask mask;			/* Saved interrupt mask		*/

	mask = disable();
	if (lock == NULL) {
		restore(mask);
		return SYSERR;
	}
	
	if (*lock == 1) {
		restore(mask);
		return 1;
	}
	else {
		*lock = 1;
		restore(mask);
		return 0;
	}
}
