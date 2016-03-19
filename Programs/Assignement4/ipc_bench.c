#include "ipc_bench.h"

int     fd[2];
timeSpec timeStart, timeEnd;
int shmtimeid;
void createTimeSharedMem(){
	if ((shmtimeid = shmget (TIMENAME, sizeof(timeSpec), IPC_CREAT | SHM_R | SHM_W )) == -1) {
   		error("shmget: shmget failed");
	}
	char *datatmp = shmat(shmtimeid, NULL, 0);
	if(datatmp == (char *)-1) {
     		error("shmop: shmat failed");
    	}
}

void main(){
	if(pipe(fd)==-1){
		error("pipe");
	}
	sem_t *sem_lead = sem_open(SEMLEAD, O_CREAT, 0644, 0);
	sem_t *sem_foll = sem_open(SEMFOLL, O_CREAT, 0644, 0);
	sem_t *sem_read = sem_open(SEMREAD, O_CREAT, 0644, 0);
	createTimeSharedMem();
	/*int shmid;
	if ((shmid = shmget (KEYNAME, SIZE, IPC_CREAT | SHM_R | SHM_W )) == -1) {
   		error("shmget: shmget failed");
	}
	char *datatmp = shmat(shmid, NULL, 0);
	if(datatmp == (char *)-1) {
     		error("shmop: shmat failed");
    	}*/
	int pid;
	if((pid= fork())==0)
		followerPipe();
	else
		leaderPipe();
	//shmdt(datatmp);
	//if(pid!=0)
    	//	shmctl(shmid, IPC_RMID, NULL);
	
	if(pid != 0){
		timeSpec *totaltime =  getTotalTime(); 
		printf("Average transfer time is : %ld sec,%ld nsec\n",totaltime->tv_sec/10,totaltime->tv_nsec/10);
		shmctl(shmtimeid, IPC_RMID, NULL);
	}
	sem_unlink(SEMLEAD);
	sem_unlink(SEMFOLL);
	sem_unlink(SEMREAD);
}

