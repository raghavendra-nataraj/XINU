#include "xinu.h"
syscall future_free(future_t* f){
	freemem(f);
}
