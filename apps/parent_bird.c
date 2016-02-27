#include <bird.h>
void parent_bird(){
	while(1){		
		mutex_lock(&babyMutex);
		cond_wait(&parentCond,&babyMutex);
		wormsLeft = num_fetch_worms;
		printf("Parent bird filled the dish with %d worms!\n",num_fetch_worms);
		cond_signal(&babyCond);
		mutex_unlock(&babyMutex);
	}
}

