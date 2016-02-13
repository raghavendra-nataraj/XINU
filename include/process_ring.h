#ifndef PROCESS_RING_H
#define PROCESS_RING_H
#define NUM_PROCESSES 4
extern volatile int inbox[];
extern volatile int count;
extern int endProcess;
extern int numberOfRounds;
#endif /*PROCESS_RING_H*/
