/* xsh_demo.c - xsh_demo*/
#include <xsh_demo.h>

int key = 567;
mutex_t shm_mutex;
cond_t shm_cond;

shellcmd xsh_demo(int32 args,char *argv[]) {
	mutex_create(&shm_mutex);
	cond_init(&shm_cond);	
	char *input;	
	if (args < 2 && strncmp(argv[1], "--help", 7) == 0) {
		printf("Usage: %s <String to share>\n ", argv[0]);
		return 0;
	}
	input = argv[1];
	resume(create(write_process,1024,20,"Write",1,input));

	resume(create(read_process,1024,20,"Read",0));
	
	return 0;
}
