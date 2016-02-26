#include <xinu.h>
syscall cond_init(cond_t* cv){
	if (lock == NULL)
		return SYSERR;
	if (test_and_set(lock)) {
		*lock = 0;
		return OK;
	}
}
