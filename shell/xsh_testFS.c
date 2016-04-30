/* xsh_hello.c - xsh_hello*/

#include <xinu.h>
#include <string.h>
#include <stdio.h>



shellcmd xsh_testFS(int32 args,char *argv[]) {
	open(LFILE0,"Ragha.txt","n");
	open(LFILE1,"Ragha1.txt","n");
	open(LFILE2,"Ragha3.txt","n");
	open(LFILE3,"Ragha4.txt","n");

	close(LFILE0);
	return 0;
}
