#include "ipc_bench.h"

void error(char *error){
	perror(error);
	exit(0);
}


char * createData(int iteration,int leader,char *data){
	long long int i =0;
	int index = 0;
	char *str = calloc(sizeof(char),8);
	for(i=(2*iteration)+leader;i<(pow(2,20) - 1 + (2 * iteration) + leader);i++){
		sprintf(str, "%lld", i);
		strncat(data,str,strlen(str));
	}
	return data;
}

void writeFile(int iteration,int leader,char *data){
	FILE *f = fopen(FILENAME,"wb");
	if(f!=NULL){
		createData(iteration,leader,data);
		fwrite(data, strlen(data), 1, f);
		fclose(f);
	}else{
		error(FILENAME);
	}
}

void readFile(char *data){
	FILE *f = fopen(FILENAME,"rb");
	if(f!=NULL){
		fseek(f, 0L, SEEK_END);
		int size = ftell(f);
		fseek(f, 0L, SEEK_SET);
		fread(data, size, 1, f);
		fclose(f);
	}else{
		error(FILENAME);
	}
}

void writeShm(int iteration,int leader,char *data){
	int shmid;
	createData(iteration,leader,data);
	if ((shmid = shmget (KEYNAME, strlen(data), SHM_R | SHM_W )) == -1) {
   		error("shmget1");
	}
	char *datatmp = shmat(shmid, NULL, 0);
	if(datatmp == (char *)-1) {
     		error("shmop");
    	}
	memcpy(datatmp,data,strlen(data));
}

void readShm(char *data){
	int shmid;
	if ((shmid = shmget (KEYNAME, strlen(data), SHM_R | SHM_W )) == -1) {
   		error("shmget2");
	}
	char *datatmp = shmat(shmid, NULL, 0);
	if(datatmp == (char *)-1) {
     		error("shmop");
    	}
	memcpy(data,datatmp,strlen(datatmp));
}

void writePipe(int iteration,int leader,char *data){
	int shmid;
	sem_t *semr = sem_open(SEMREAD, 0); 
	createData(iteration,leader,data);
	//close(fd[0]);
	sem_post(semr);
	write(fd[1],data,strlen(data));
}

void verify(int iteration,int who){
	char* data = (char*)calloc(sizeof(char) , pow(2,30));
	char* data1 = (char*)calloc(sizeof(char) , pow(2,30));
	createData(iteration,who,data);
	readData(data1);
	//printf("data = %s\n",data);
	//printf("data1 = %s\n",data1);
	if(strncmp(data,data1,strlen(data1))!=0){
		printf("Not Matching\n");
		exit(0);
	}
	free(data);
	free(data1);
	
}


void readPipe(char *data){
	int n;
	sem_t *semr = sem_open(SEMREAD, 0); 
	fd_set readFd;
	char *tempBuff = malloc(sizeof(char)*pow(2,10));
	FD_ZERO(&readFd);
	struct timeval timeOut;
	timeOut.tv_sec = 1;
	timeOut.tv_usec = 0;
	FD_SET(fd[0],&readFd);
	sem_wait(semr);
	while(select(fd[0]+1,&readFd,NULL,NULL,&timeOut)){
		bzero(tempBuff,pow(2,10));
		n = read(fd[0],tempBuff,pow(2,10));
		if(n<0){error("reading failed");}
		strncat(data,tempBuff,pow(2,10));
	}
	//printf("%s",data);
}



void writeData(int iteration,int leader,char *data){
	//writeFile(iteration,leader,data);
	//writeShm(iteration,leader,data);
	writePipe(iteration,leader,data);
}

void readData(char *data){
	//readFile(data);
	//readShm(data);
	readPipe(data);	
}
