#include <xsh_demo.h>
void write_process(char *input){

	uint16 id;
	char *addr;
	id = shmget(key,strlen(input),SHM_EXIST);
	if(id==SYSERR){
		printf("Shared Memory Error\n");
		exit(0);
	}
 	addr = shmat(id,NULL,0);
	if(addr==NULL){
		printf("Shared Memory Error\n");
		exit(0);
	}
	strcpy(addr,input);
	cond_signal(&shm_cond);
}
