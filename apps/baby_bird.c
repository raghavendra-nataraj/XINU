#include <bird.h>
void baby_bird(int id){	
	while(1){
		if(wormsLeft==0)
			signal(empty);
		wait(mutex);
		wormsLeft--;
		printf("Baby %d eating worm %d\n",id,wormsLeft);
		signal(mutex);
		sleep(1);
	}
}
