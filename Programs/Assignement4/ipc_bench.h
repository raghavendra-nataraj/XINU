#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h> 	
#include <sys/stat.h> 
#include <sys/wait.h>
#define SEMLEAD "LEADLOCK"
#define SEMFOLL "FOLLLOCK"
#define SEMREAD "READLOCK"
#define FOLLOWER 0
#define LEADER 1
#define FILENAME "benchMark.txt"
#define KEYNAME 22222
extern int     fd[];



//helper.c
void error(char *error);
char * createData(int iteration,int leader,char *data);
void writeFile(int iteration,int leader,char *data);
void readFile(char *data);
void writeShm(int iteration,int leader,char *data);
void readShm(char *data);
void writePipe(int iteration,int leader,char *data);
void verify(int iteration,int who);
void readPipe(char *data);
void writeData(int iteration,int leader,char *data);
void readData(char *data);

//follower.c
void followerPipe();
void follower();

//leader.c
void leaderPipe();
void leader();
