#include <bird.h>
void baby_bird(int id){	
int i=0;
	while(i < num_eat_worms){
		mutex_lock(&babyMutex);
		if(wormsLeft == 0){
			//printf("hello\n");
			cond_signal(&parentCond);
			mutex_lock(&babyMutex1);
			cond_wait(&babyCond,&babyMutex1);
			mutex_unlock(&babyMutex1);
		}
		
		printf("Baby bird %d ate a worm! worm %d\n",id,wormsLeft);
		wormsLeft--;
		i++;
		//cond_signal(&babyCond);
		mutex_unlock(&babyMutex);
		resched();

	}

	babyExited++;
	if(babyExited==num_baby_birds)
		cond_signal(&parentCond);
}

