#include "ipc_bench.h"


void leaderPipe(){
	int i;
	sem_t *seml = sem_open(SEMLEAD, 0); 
	sem_t *semf = sem_open(SEMFOLL, 0); 
	char* data = (char*)calloc(sizeof(char) , pow(2,30));
	int shmid;
	for(i=0;i<10;i++){
		bzero(data,pow(2,30));
		printf("Leader=%d\n",i);
		writeData(i,FOLLOWER,data);
		sem_wait(seml);
		verify(i,LEADER);
		sem_post(semf);
	}
	free(data);
}


void leader(){
	int i;
	sem_t *seml = sem_open(SEMLEAD, 0); 
	sem_t *semf = sem_open(SEMFOLL, 0); 
	char* data = (char*)calloc(sizeof(char) , pow(2,30));
	int shmid;
	for(i=0;i<10;i++){
		sem_wait(seml);
		bzero(data,pow(2,30));
		printf("Leader=%d\n",i);
		writeData(i,FOLLOWER,data);
		sem_post(semf);
		sem_wait(seml);
		verify(i,LEADER);


	}
	free(data);
}
