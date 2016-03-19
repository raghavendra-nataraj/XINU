#include "ipc_bench.h"


void error(char *error){
	perror(error);
	exit(0);
}

timeSpec* getTotalTime(){
	int shmid;
	if ((shmid = shmget (TIMENAME, sizeof(timeSpec), SHM_R | SHM_W )) == -1) {
   		error("shmget1");
	}
	timeSpec *timetemp = shmat(shmid, NULL, 0);
	if(timetemp == (timeSpec *)-1) {
     		error("shmop");
    	}
	return timetemp;
}

timeSpec timediff(timeSpec timeEnd,timeSpec timeStart){
	timeSpec diff;
	if(timeEnd.tv_nsec - timeStart.tv_nsec < 0){
		diff.tv_sec = timeEnd.tv_sec-timeStart.tv_sec-1;
		diff.tv_nsec = 1000000000 + timeEnd.tv_nsec-timeStart.tv_nsec;
	}else{
		diff.tv_sec = timeEnd.tv_sec-timeStart.tv_sec;
		diff.tv_nsec = timeEnd.tv_nsec-timeStart.tv_nsec;
	}

	return diff;
}

void timeadd(timeSpec time1,timeSpec *time2){
	if((time1.tv_nsec + time2->tv_nsec) > 1000000000){
		time2->tv_sec = time1.tv_sec+time2->tv_sec+1;
		time2->tv_nsec = time2->tv_nsec + time1.tv_nsec -1000000000 ;
	}else{
		time2->tv_sec = time2->tv_sec+time1.tv_sec;
		time2->tv_nsec = time2->tv_nsec+time1.tv_nsec;
	}

}

long * createData(int iteration,int leader,long *data){
	long i =0;
	int index = 0;
	for(index=0,i=(2*iteration)+leader;i<(pow(2,20) - 1 + (2 * iteration) + 2*leader);i++,index++){
		data[index] = i;	
	}
	return data;
}

void writeFile(int iteration,int leader,long *data){
	FILE *f = fopen(FILENAME,"wb");
	if(f!=NULL){
		createData(iteration,leader,data);
		fwrite(data,sizeof(long),  pow(2,20), f);
		fclose(f);
	}else{
		error(FILENAME);
	}
}

void readFile(long *data){
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

void writeShm(int iteration,int leader,long *data){
	int shmid;
	createData(iteration,leader,data);
	if ((shmid = shmget (KEYNAME, SIZE, SHM_R | SHM_W )) == -1) {
   		error("shmget1");
	}
	char *datatmp = shmat(shmid, NULL, 0);
	if(datatmp == (char *)-1) {
     		error("shmop");
    	}
	//printf("%ld\n",data[0]);
	memcpy(datatmp,data,SIZE);
}

void readShm(long *data){
	int shmid;
	if ((shmid = shmget (KEYNAME,SIZE, SHM_R | SHM_W )) == -1) {
   		error("shmget2");
	}
	long *datatmp = shmat(shmid, NULL, 0);
	if(datatmp == (long *)-1) {
     		error("shmop");
    	}
	//printf("ff%ld\n",datatmp[0]);
	memcpy(data,datatmp,SIZE);
}

void writePipe(int iteration,int leader,long *data){
	int shmid;
	sem_t *semr = sem_open(SEMREAD, 0); 
	createData(iteration,leader,data);
	//close(fd[0]);
	sem_post(semr);
	write(fd[1],data,SIZE);
}


void readPipe(long *data){
	int n;
	long *tempBuff = data;
	sem_t *semr = sem_open(SEMREAD, 0); 
	fd_set readFd;
	//char *tempBuff = malloc(sizeof(char)*pow(2,10));
	FD_ZERO(&readFd);
	struct timeval timeOut;
	timeOut.tv_sec = 0;
	timeOut.tv_usec = 20000;
	FD_SET(fd[0],&readFd);
	sem_wait(semr);
	while(select(fd[0]+1,&readFd,NULL,NULL,&timeOut)){
		//bzero(tempBuff,pow(2,10));
		n = read(fd[0],tempBuff,pow(2,10));
		if(n<0){error("reading failed");}
		tempBuff =(long*)( (char*)tempBuff+n);
	}
	//printf("%s",data);
}

void verify(int iteration,int who){
	long* data = (long*)calloc(sizeof(long) , pow(2,20));
	long* data1 = (long*)calloc(sizeof(long) , pow(2,20));
	int i;
	createData(iteration,who,data);
	readData(data1);
	for(i=0;i<pow(2,20);i++){
		//printf("%d %d %ld = %ld\n",who,iteration,data[i],data1[i]);
		if(data[i]!=data1[i]) {
			printf("Not Matching");
			exit(0);
		}
	}
	free(data);
	free(data1);
	
}


void writeData(int iteration,int leader,long *data){
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&timeStart);
	//writeFile(iteration,leader,data);
	//writeShm(iteration,leader,data);
	writePipe(iteration,leader,data);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&timeEnd);
	timeSpec diff = timediff(timeEnd,timeStart); 
	timeSpec *totaltime =  getTotalTime(); 
	timeadd(diff,totaltime); 
}

void readData(long *data){
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&timeStart);
	//readFile(data);
	//readShm(data);
	readPipe(data);	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&timeEnd);
	timeSpec diff = timediff(timeEnd,timeStart); 
	timeSpec *totaltime =  getTotalTime(); 
	timeadd(diff,totaltime); 
}
