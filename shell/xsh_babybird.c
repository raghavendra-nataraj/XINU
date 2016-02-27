/* xsh_babybird.c - xsh_babybird*/
#include <bird.h>
int num_baby_birds = 0;
int num_fetch_worms = 0;
int num_eat_worms = 0;
volatile int babyExited = 0;
volatile int wormsLeft = 0;	
volatile mutex_t babyMutex;
volatile mutex_t parentMutex;
volatile cond_t parentCond;
volatile cond_t babyCond;
shellcmd xsh_babybird(int32 args,char *argv[]) {
	int i;
	num_baby_birds = 0;
	num_fetch_worms = 0;
	num_eat_worms = 0;	
	babyExited = 0;
	wormsLeft = 0;
	num_baby_birds = atoi(argv[1]);
	num_fetch_worms = atoi(argv[2]);
	num_eat_worms = atoi(argv[3]);
	mutex_create(&babyMutex);
	cond_init(&babyCond);
	cond_init(&parentCond);		
	if (args < 4 && strncmp(argv[1], "--help", 7) == 0) {
		printf("Usage: %s <number of babybirds> <number of fetch worms> <number of worms baby to eat>\n\n ", argv[0]);
		return 0;
	}
	resume(create(parent_bird,1024,20,"Parent",0));
	for(i=0;i< num_baby_birds;i++)
	{
		resume(create(baby_bird,1024,20,"Baby",1,i));
	}
	
	return 0;
}
