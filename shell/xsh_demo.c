/* xsh_demo.c - xsh_demo*/
#include <xinu.h>
int key = 567;
mutex_t shm_mutex;
cond_t shm_cond;
void write_process(char *input){

	uint16 id;
	char *addr;
	id = shmget(key,strlen(input),0);
	printf("id=%d\n",id);
 	addr = shmat(id,NULL,0);
	strcpy(addr,input);
	printf("%s",addr);
	cond_signal(&shm_cond);
}

void read_process(){

	mutex_lock(&shm_mutex);
	cond_wait(&shm_cond,&shm_mutex);
	mutex_unlock(&shm_mutex);
	uint16 id;
	char *addr;
	id = shmget(key,0,0);
	printf("id=%d\n",id);
 	addr = shmat(id,NULL,0);
	if(addr==NULL) printf("sjdahlshd");
	printf("Read \"%s\" from shared memory",addr);
}

shellcmd xsh_demo(int32 args,char *argv[]) {
	mutex_create(&shm_mutex);
	cond_init(&shm_cond);	
	char *input;	
	if (args < 2 && strncmp(argv[1], "--help", 7) == 0) {
		printf("Usage: %s <number of babybirds> <number of fetch worms> <number of worms baby to eat>\n\n ", argv[0]);
		return 0;
	}
	input = argv[1];
	resume(create(write_process,1024,20,"Write",1,input));

	resume(create(read_process,1024,20,"Read",0));
	
	return 0;
}
