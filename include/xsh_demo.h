#ifndef XSH_DEMO_H
#define XSH_DEMO_H
#include <xinu.h>
extern int key;
extern mutex_t shm_mutex;
extern cond_t shm_cond;
void read_process();
void write_process(char *input);
#endif /*XSH_DEMO_H*/
