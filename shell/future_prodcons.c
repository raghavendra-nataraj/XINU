/* xsh_prodcons.c - xsh_prodcons */

#include <xinu.h>
#include <stdio.h>
#include <future.h>

/*------------------------------------------------------------------------
 * xhs_echo - write argument strings to stdout
 *------------------------------------------------------------------------
 */
shellcmd xsh_prodcons(int nargs, char *args[])
{
	future_t* f_exclusive,
          * f_shared,
          * f_queue;

  f_exclusive = future_alloc(FUTURE_EXCLUSIVE);

	return 0;
}
