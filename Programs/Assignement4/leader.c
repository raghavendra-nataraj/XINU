#include "ipc_bench.h"


void leaderPipe(){
	int i;
	sem_t *seml = sem_open(SEMLEAD, 0); 
	sem_t *semf = sem_open(SEMFOLL, 0); 
	long* data = (long*)calloc(sizeof(long) , pow(2,20));
	int shmid;
	for(i=0;i<10;i++){
		bzero(data,SIZE);
		printf("Leader=%d\n",i);
		writeData(i,LEADER,data);
		sem_wait(seml);
		verify(i,FOLLOWER);
		sem_post(semf);
		//printf("Time per iteration : %f sec",totaltime);		
	}
	
	//printf("Time : %f sec",totaltime);
        //totalavg.tv_sec /= 10;
        //totalavg.tv_nsec /= 10;
	free(data);
}


void leader(){
	int i;
	sem_t *seml = sem_open(SEMLEAD, 0); 
	sem_t *semf = sem_open(SEMFOLL, 0); 
	long* data = (long*)calloc(sizeof(long) , pow(2,20));
	int shmid;
	for(i=0;i<10;i++){
		sem_wait(seml);
		bzero(data,SIZE);
		printf("Leader=%d\n",i);
		writeData(i,LEADER,data);
		sem_post(semf);
		sem_wait(seml);
		verify(i,FOLLOWER);
	}
	free(data);
}
