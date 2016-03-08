#include <xinu.h>
char *shmat(int16 shmid,char *shmaddr, int16 shmflag){
	if(shmtab[shmid].key == -1)
		return NULL;
	return shmtab[shmid].shmemory;
}
