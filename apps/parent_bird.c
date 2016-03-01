#include <bird.h>
void parent_bird(){
	while(1){		
		mutex_lock(&parentMutex);
		cond_wait(&parentCond,&parentMutex);
		if(babyExited==num_baby_birds)
			break;
		wormsLeft = num_fetch_worms;
		printf("Parent bird filled the dish with %d worms!\n",num_fetch_worms);
		cond_signal(&babyCond);
		mutex_unlock(&parentMutex);
	}
	printf("Number of worms left in the disk = %d",wormsLeft);
}

