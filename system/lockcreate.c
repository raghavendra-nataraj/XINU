/* lockcreate.c - lockcreate */

#include <xinu.h>

typedef int32 lock32;


/*------------------------------------------------------------------------
 *  lockcreate  -  Create a new lock and return the ID to the caller
 *------------------------------------------------------------------------
 */
lock32*	lockcreate(
	  int32		set		/* Initial lock status	*/
	)
{
	intmask	mask;			/* Saved interrupt mask	*/
	lock32* lock;			/* Lock Pointer to return	*/

	mask = disable();
	lock = (lock32*)malloc(sizeof(lock32));	
	*lock = set;
	restore(mask);
	return lock;
}
