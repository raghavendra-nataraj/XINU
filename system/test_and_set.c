/* test_and_set.c - test_and_set */

#include <xinu.h>


/*------------------------------------------------------------------------
 *  test_and_set -  Sets the lock and return its previous state.
 *------------------------------------------------------------------------
 */
syscall test_and_set(
	  mutex_t*	lock		/* Pointer to lock*/
	)
{
	if (lock == NULL)
		return SYSERR;

	intmask	mask;			/* Saved interrupt mask	*/

	mask = disable();

	mutex_t prev;
	prev = *lock;	
	*lock = 1;

	restore(mask);

	return prev;
}
