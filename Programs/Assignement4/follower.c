#include "ipc_bench.h"

void followerPipe(){
	int i;
	sem_t *seml = sem_open(SEMLEAD, 0); 
	sem_t *semf = sem_open(SEMFOLL, 0); 
	long* data = (long*)calloc(sizeof(long) , pow(2,20));
	for(i=0;i<10;i++){	
		bzero(data,SIZE);
		verify(i,LEADER);
		sem_post(seml);
		printf("Follower=%d\n",i);
		writeData(i,FOLLOWER,data);		
		sem_wait(semf);
	}
	free(data);
}

void follower(){
	int i;
	sem_t *seml = sem_open(SEMLEAD, 0); 
	sem_t *semf = sem_open(SEMFOLL, 0); 
	long* data = (long*)calloc(sizeof(long) , pow(2,20));
	for(i=0;i<10;i++){	
		sem_post(seml);
		sem_wait(semf);
		bzero(data,SIZE);
		printf("Follower=%d\n",i);
		verify(i,LEADER);
		writeData(i,FOLLOWER,data);
		sem_post(seml);		
	}
	free(data);
}

