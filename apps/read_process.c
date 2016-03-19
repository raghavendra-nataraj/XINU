#include <xsh_demo.h>
void read_process(){

	mutex_lock(&shm_mutex);
	cond_wait(&shm_cond,&shm_mutex);
	mutex_unlock(&shm_mutex);
	uint16 id;
	char *addr;
	id = shmget(key,0,SHM_FETCH);
	if(id==SYSERR){
		printf("Shared Memory Error\n");
		exit(0);
	}
 	addr = shmat(id,NULL,0);
	if(addr==NULL){
		printf("Shared Memory Error\n");
		exit(0);
	}
	printf("Read \"%s\" from shared memory\n",addr);
}
