#include <xinu.h>
char *shmat(int16 shmid,char *shmaddr, int16 shmflag){
	char *temp;
	if(shmtab[shmid].key == -1)
		return NULL;
	shmtab[shmid].refcount+=1;
	if(shmflag == SHM_RND){
		if(shmaddr !=NULL){
	 		shmaddr =  shmtab[shmid].shmemory;
			return shmaddr;
		}
		else{
			temp = shmtab[shmid].shmemory;
			return temp;	
		}
	}
	/* shmflag = SHM_RDONLY */
	temp = shmtab[shmid].shmemory;
	return temp;
	
}
