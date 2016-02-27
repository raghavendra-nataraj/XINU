#include <bird.h>
void baby_bird(int id){	
int i=0;
	while(i < num_eat_worms){
		mutex_lock(&babyMutex);
		cond_wait(&babyCond,&babyMutex);
		if(wormsLeft == 0){
			cond_signal(&parentCond);
			cond_wait(&babyCond,&babyMutex);
		}
		
		printf("Baby bird %d ate a worm! worm %d,%d\n",id,wormsLeft,i);
		wormsLeft--;
		i++;
		cond_signal(&babyCond);
		mutex_unlock(&babyMutex);

	}
}

