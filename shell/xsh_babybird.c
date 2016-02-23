/* xsh_babybird.c - xsh_babybird*/
#include <bird.h>
int babyCount;
int wormsCount;
int wormsLeft;
sid32 empty;
sid32 mutex;
shellcmd xsh_babybird(int32 args,char *argv[]) {
	int i;
	empty = semcreate(0);
	mutex = semcreate(1);		
	if (args < 3 && strncmp(argv[1], "--help", 7) == 0) {
		printf("Usage: %s <number of babybirds> <number of worms>\n\n ", argv[0]);
		return 0;
	}
	babyCount = atoi(argv[1]);
	wormsCount = atoi(argv[2]);
	wormsLeft = wormsCount;
	resume(create(parent_bird,1024,20,"Parent",0));
	for(i=0;i< babyCount;i++)
	{
		resume(create(baby_bird,1024,20,"Baby",1,i));
	}
	return 0;
}
