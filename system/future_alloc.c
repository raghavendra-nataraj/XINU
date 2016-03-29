#include "xinu.h"
#include "future.h"
future_t* future_alloc(future_mode_t mode) {

	future_t* future_obj=(future_t*) getmem(sizeof(future_t));
	if(future_obj == (future_t*)SYSERR)
		return NULL;
	future_obj->mode = mode;
	future_obj->state = FUTURE_EMPTY;
	future_obj->pid = 0;
	future_obj->set_queue = newqueue();
	future_obj->get_queue = newqueue();
	return future_obj;
}
