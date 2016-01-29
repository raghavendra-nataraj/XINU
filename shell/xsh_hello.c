/* xsh_hello.c - xsh_hello*/

#include <xinu.h>
#include <string.h>
#include <stdio.h>



shellcmd xsh_hello(int32 args,char *argv[]) {
	if (args > 2) {
		fprintf(stderr, "%s: too many arguments\n", argv[0]);
		fprintf(stderr, "Try '%s --help' for more information	\n",
			argv[0]);
		return 1;
	}
	if (args < 2) {
		fprintf(stderr, "%s: too few arguments\n", argv[0]);
		fprintf(stderr, "Try '%s --help' for more information	\n",
			argv[0]);
		return 1;
	}
	if (args == 2 && strncmp(argv[1], "--help", 7) == 0) {
		printf("Usage: %s <string>\n\n ", argv[0]);
		printf("Description:\n");
		printf("Prints additional string\n");
		return 0;
	}
	printf("Hello ");
	printf("%s ",argv[1]);
	printf("Welcome to the world of Xinu!!\n");
	return 0;
}
