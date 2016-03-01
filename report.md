The program implements mutex and conditional variables using test_and_set. The interrupts are only disabled in in the test_and_set function, which diables the interupts tests the value of the lock/mutex, sets it ,enable the interrupts and then returns the previous value.Mutex and Conditional variables are created using mutex_create and cond_init system calls. Mutex_lock and cond_wait works on the principle of busy wait. If the test_and_set(&lock) returns 1, the threads continue to spin in the while loop till some other thread unlocks/signal it. The cond_wait unlocks the mutex associated mutex and then busy waits. After the conditional variable is signaled it comes out of the loop and acquires the mutex back. The syscall mutex_unlock and cond_signal unsets the mutex/condition variable.

The program has following system call files :
  1. mutex_create.c
  2. mutex_lock.c
  3. mutex_unlock.c
  4. cond_init.c
  5. cond_wait.c
  6. cond_signal.c 

Working of the program :
First the parent process is created and starts execution. It acquires parentmutex lock and wait on the parent condition. N Baby processes are created and starts execution. Initialy the wormleft in the dish is zero and the babybird process which acquires the babymutex first signals the parent's condition variable and waits on baby condition variable and babymutex1. The parent process starts executing and sets the wormleft to the refil value and then signals the baby conditional variable and wait on the parent condition variable. When the baby condition variable is signaled from the parent process, the baby process acquires the babymutex1 (it already had the babymutex lock) and starts execution, eats the worm and then releases the babymutex lock. The whole process continues till each baby has eaten its share of worms. Whenever the baby process exits it incremeants the global variable. When the global variable becomes equal to number of baby birds, the last babybird before exiting signals the parent conditional variable. The parent process checks the condition and when the global varible is equal to number of baby it breaks from the while loop and prints the worms left in the dish and then exits.  
