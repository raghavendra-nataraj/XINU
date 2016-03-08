#include <xsh_demo.h>
void read_process(){

	mutex_lock(&shm_mutex);
	cond_wait(&shm_cond,&shm_mutex);
	mutex_unlock(&shm_mutex);
	uint16 id;
	char *addr;
	id = shmget(key,0,SHM_EXIST);
	printf("id=%d\n",id);
 	addr = shmat(id,NULL,0);
	printf("Read \"%s\" from shared memory\n",addr);
}
