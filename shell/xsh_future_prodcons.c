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
shellcmd xsh_prodcons(int nargs, char *argv[])
{

	if (nargs > 2) {
		fprintf(stderr, "%s: too many arguments\n", argv[0]);
		fprintf(stderr, "Try '%s --help' for more information	\n",
			argv[0]);
		return 1;
	}
	if (nargs == 2 && strncmp(argv[1], "--help", 7) == 0) {
		printf("Usage: %s -r\n ", argv[0]);
		printf(" -r is optional\n");
		return 0;
	}
	future_t* f;
	future_t* f_exclusive,
        	* f_shared,
          	* f_queue;
	if (nargs == 2 && strncmp(argv[1], "-r", 3) == 0) {
		
	  	//f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
	  	//f = f_exclusive;
	  	//f_shared    = future_alloc(FUTURE_SHARED);
  	  	//f = f_shared;
  	  	f_queue     = future_alloc(FUTURE_QUEUE);
  	  	f = f_queue;
  // Test FUTURE_EXCLUSIVE
  //resume( create(future_cons, 1024, 20, "fcons2", 1, f_exclusive) );
  		/*resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
         	resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );*/
 


  		/*resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
        	resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
  		resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
        	resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
        	resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );*/
  //resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );

  		resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
  		resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
        	resume( create(future_cons, 1024, 20, "fcons8", 1, f_queue) );
        	resume( create(future_cons, 1024, 20, "fcons9", 1, f_queue) );
        	resume( create(future_prod, 1024, 20, "fprod3", 1, f_queue) );
        	resume( create(future_prod, 1024, 20, "fprod4", 1, f_queue) );
        	resume( create(future_prod, 1024, 20, "fprod5", 1, f_queue) );
        	resume( create(future_prod, 1024, 20, "fprod6", 1, f_queue) );
	}else{

		f_shared    = future_alloc(FUTURE_SHARED);
  	  	f = f_shared;

		resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
        	resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
  		resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
        	resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
        	resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );
  		resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );

	}
	
	while(!isempty(f->get_queue) || !isempty(f->set_queue)){resched();}
	sleep(1);
	future_free(f);
	return 0;
}
