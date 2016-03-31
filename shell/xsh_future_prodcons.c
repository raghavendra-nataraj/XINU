/* xsh_prodcons.c - xsh_prodcons */

#include <xinu.h>
#include <stdio.h>
#include <future.h>

uint32 future_prod(future_t* fut);
uint32 future_cons(future_t* fut);
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
  f_shared    = future_alloc(FUTURE_SHARED);
  f_queue     = future_alloc(FUTURE_QUEUE);
  // Test FUTURE_EXCLUSIVE
  resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
  resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );
  resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) ); 


  /*resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
  resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
  resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
  resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
  resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );*/

  /*resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
  resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
  resume( create(future_cons, 1024, 20, "fcons8", 1, f_queue) );
  resume( create(future_cons, 1024, 20, "fcons9", 1, f_queue) );
  resume( create(future_prod, 1024, 20, "fprod3", 1, f_queue) );
  resume( create(future_prod, 1024, 20, "fprod4", 1, f_queue) );
  resume( create(future_prod, 1024, 20, "fprod5", 1, f_queue) );
  resume( create(future_prod, 1024, 20, "fprod6", 1, f_queue) );*/
	
	//future_free(f_exclusive);
	return 0;
}
