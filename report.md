The program implements mutex and conditional variables using test_and_set. The interrupts are only disabled in in the test_and_set function, which disables the interupts tests the value of the lock/mutex, sets it ,enable the interrupts and then returns the previous value.Mutex and Conditional variables are created using mutex_create and cond_init system calls. Mutex_lock and cond_wait works on the principle of busy wait. If the test_and_set(&lock) returns 1, the threads continue to spin in the while loop till some other thread unlocks/signal it. The cond_wait unlocks the mutex associated mutex and then busy waits. After the conditional variable is signaled it comes out of the loop and acquires the mutex back. The syscall mutex_unlock and cond_signal unset the mutex/condition variable.

The program has following system call files :
  1. mutex_create.c
  2. mutex_lock.c
  3. mutex_unlock.c
  4. cond_init.c
  5. cond_wait.c
  6. cond_signal.c 

Working of the program :
First the parent process is created and starts execution. It acquires parent mutex lock and wait on the parent condition. N Baby processes are created and starts execution. Initially the wormleft in the dish is zero and the babybird process which acquires the babymutex first signals the parent's condition variable and waits on baby condition variable and babymutex1. The parent process starts executing and sets the wormleft to the refill value and then signals the baby conditional variable and wait on the parent condition variable. When the baby condition variable is signaled from the parent process, the baby process acquires the babymutex1 (it already had the babymutex lock) and starts execution, eats the worm and then releases the babymutex lock. The whole process continues till each baby has eaten its share of worms. Whenever the baby process exits it increments the global variable. When the global variable becomes equal to number of baby birds, the last babybird before exiting signals the parent conditional variable. The parent process checks the condition and when the global variable is equal to number of baby it breaks from the while loop and prints the worms left in the dish and then exits.  


Questions:

1. Starvation is a state when thread(s) wait to access a resource but the resource never is never available .There can be a situation when a process is context switch due to timer interrupt right after it sets busy to true, but before checking the while condition and exiting the loop. In that case busy would be set to true and the process setting it to true is context switched before exiting the loop. Now all the threads executing after that would loop inside the inner do while loop and will set the turn variable accordingly. By the time previous thread gets to execute again the turn would be set to some other thread and hence would not be able to exit the outer loop and will also start looping inside the inner loop as there is no chance for busy to be set to false again (because none has yet acquired the lock).

2. Deadlock is a state when the threads/processes are in cyclic dependency, where thread(s) are awaiting a resource to be freed by another thread(s) which in turn waits for this thread to free the another resource. This protocol is DEADLOCK free because in no situation will any thread wait on a unlock to free the available resource.
