#include <bird.h>
void parent_bird(){
	while(1){
		wait(empty);
		wait(mutex);
		wormsLeft = wormsCount;
		printf("Parent filling: worms count %d\n",wormsLeft);
		signal(mutex);
	}
}
