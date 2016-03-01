#include <xinu.h>
#include <string.h>
#include <stdio.h>
extern int num_baby_birds;
extern int num_fetch_worms;
extern int num_eat_worms;
extern volatile int wormsLeft;	
extern volatile int babyExited;	
extern volatile mutex_t babyMutex;
extern volatile mutex_t babyMutex1;
extern volatile mutex_t parentMutex;
extern volatile cond_t parentCond;
extern volatile cond_t babyCond;
void baby_bird(int id);
void parent_bird();
