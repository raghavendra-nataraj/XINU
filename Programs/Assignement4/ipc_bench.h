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
#include <time.h>
#define SEMLEAD "LEADLOCK"
#define SEMFOLL "FOLLLOCK"
#define SEMREAD "READLOCK"
#define FOLLOWER 1
#define LEADER 0
#define FILENAME "/tmp/benchMark.txt"
#define KEYNAME 2221
#define TIMENAME 2211
#define SIZE (pow(2,20) * sizeof(long))
extern int     fd[];
typedef struct timespec timeSpec;
extern timeSpec timeStart, timeEnd;

//helper.c
void error(char *error);
long * createData(int iteration,int leader,long *data);
void writeFile(int iteration,int leader,long *data);
void readFile(long *data);
void writeShm(int iteration,int leader,long *data);
void readShm(long *data);
void writePipe(int iteration,int leader,long *data);
void verify(int iteration,int who);
void readPipe(long *data);
void writeData(int iteration,int leader,long *data);
void readData(long *data);
timeSpec* getTotalTime(void);

//follower.c
void followerPipe();
void follower();

//leader.c
void leaderPipe();
void leader();

timeSpec timediff(timeSpec timeEnd,timeSpec timeStart);
void timeadd(timeSpec time1,timeSpec *time2);
