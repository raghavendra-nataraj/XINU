#include "ipc_bench.h"

int     fd[2];

void main(){
	if(pipe(fd)==-1){
		error("pipe");
	}
	sem_t *sem_lead = sem_open(SEMLEAD, O_CREAT, 0644, 0);
	sem_t *sem_foll = sem_open(SEMFOLL, O_CREAT, 0644, 0);
	sem_t *sem_read = sem_open(SEMREAD, O_CREAT, 0644, 0);
	/*int shmid;
	if ((shmid = shmget (KEYNAME, pow(2,30), IPC_CREAT | SHM_R | SHM_W )) == -1) {
   		error("shmget: shmget failed");
	}
	char *datatmp = shmat(shmid, NULL, 0);
	if(datatmp == (char *)-1) {
     		error("shmop: shmat failed");
    	}*/
	int pid;
	if(pid== fork())
		followerPipe();
	else
		leaderPipe();
	//shmdt(datatmp);
	//if(pid!=0)
    		//shmctl(shmid, IPC_RMID, NULL);

}

