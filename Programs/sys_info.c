#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc,char *argv[]){
	if(argc<2){
		fprintf(stderr,"Usage : %s <command>\n",argv[0]);
		return 0;
	}
	int pfd[2];
	int pid;
	if(pipe(pfd)== -1)	{
		perror("Pipe");
		return 0;
	}
	char arg1[] = "Hello World!";
	pid = fork();
	if(pid == -1)	{
		perror("fork");
		return 0;
	}
	if(pid==0)	{
		printf("Child\tID = %d \n", pid);
		char buf[512];
		bzero(&buf,512);
		close(pfd[1]);
		read(pfd[0],&buf,511);
		buf[511] = '\0';
		if(strcmp(buf,"echo")==0){
			strcat(buf," $0");
			execl("/bin/sh","/bin/sh","-c",buf,arg1,(char*)0);	
		}
		execl("/bin/sh","/bin/sh","-c",buf,(char*)0);
	}else{
		printf("Parent\tID = %d \n",pid);
		close(pfd[0]);
		write(pfd[1],argv[1],strlen(argv[1]));
		wait(NULL);
	}
	return 0;
}
