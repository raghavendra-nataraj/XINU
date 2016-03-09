#include <xinu.h>
char *shmat(int16 shmid,char *shmaddr, int16 shmflag){
	char *temp;
	if(shmtab[shmid].key == -1)
		return NULL;
	if(shmaddr !=NULL)
	{
	 	shmaddr =  shmtab[shmid].shmemory;
		return shmaddr;
	}
	temp = shmtab[shmid].shmemory;
	return temp;
	
}
