#include <xinu.h>
#include <string.h>
#include <stdio.h>
extern int wormsCount;
extern int wormsLeft;
extern sid32 empty;
extern sid32 mutex;
void baby_bird(int id);
void parent_bird();
