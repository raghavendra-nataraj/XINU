#include <xinu.h>
char *shmdt(int16 shmid, int16 shmflag){
	struct shment *shmptr;
	shmptr = &shmtab[shmid];
	shmptr->key = -1;
	shmptr->refcount = 0;
	freemem(shmptr->shmemory,shmptr->size);
	shmptr->size = 0;
	shmptr->shmemory = NULL;
	return NULL;
}
