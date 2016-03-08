#include <xinu.h>
uint16 shmget(int16 key, uint32 size, int16 flag){
	int i;
	struct shment *shmptr;
	for (i = 0; i < NSHMENT; i++) {
		if(shmtab[i].key == key){
			if((flag) == SHM_CREAT){
				return -1;		
			}else{
				return i;
			}
		}		
		if(shmtab[i].key != -1){
			continue;
		}
		break;
	}
	if((flag & SHM_FETCH) != SHM_FETCH){
		return -1;	
	}	
	shmptr = &shmtab[i];
	shmptr->key = key;
	shmptr->refcount = 0;
	shmptr->size = size;
	if((shmptr->shmemory = getmem(sizeof(char)*size))==SYSERR){
		return -1;
	}else{
		return i;
	}
	return -1;
}
