#include <xsh_demo.h>
void write_process(char *input){

	uint16 id;
	char *addr;
	id = shmget(key,strlen(input),SHM_EXIST);
 	addr = shmat(id,NULL,0);
	strcpy(addr,input);
	printf("%s",addr);
	cond_signal(&shm_cond);
}
