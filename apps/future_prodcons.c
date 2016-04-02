#include <xinu.h>
#include <future.h>
uint32 future_prod(future_t* fut) {
  int i, j;
   
  j = (int)fut;
  for (i = 0; i < 1000; ++i) {
    j += i;
  }
  int status = future_set(fut, j);
  if (status < 1) {
	printf("future_set failed\n");
	return SYSERR;
	}
  return OK;
}

uint32 future_cons(future_t* fut) {
  int i, status;
  status = (int)future_get(fut, &i);
  if (status < 1) {
    printf("future_get failed\n");
    return -1;
  }
  printf("it produced %d\n", i);
  return OK;
}
