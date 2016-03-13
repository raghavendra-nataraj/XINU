#include "ipc_bench.h"

void followerPipe(){
	int i;
	sem_t *seml = sem_open(SEMLEAD, 0); 
	sem_t *semf = sem_open(SEMFOLL, 0); 
	char* data = (char*)calloc(sizeof(char) , pow(2,30));
	for(i=0;i<10;i++){	
		bzero(data,pow(2,30));
		verify(i,FOLLOWER);
		sem_post(seml);
		printf("Follower=%d\n",i);
		writeData(i,LEADER,data);		
		sem_wait(semf);
	}
	free(data);
}

void follower(){
	int i;
	sem_t *seml = sem_open(SEMLEAD, 0); 
	sem_t *semf = sem_open(SEMFOLL, 0); 
	char* data = (char*)calloc(sizeof(char) , pow(2,30));
	for(i=0;i<10;i++){	
		sem_post(seml);
		sem_wait(semf);
		bzero(data,pow(2,30));
		printf("Follower=%d\n",i);
		verify(i,FOLLOWER);
		writeData(i,LEADER,data);
		sem_post(seml);		
	}
	free(data);
}

