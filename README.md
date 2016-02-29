# Spring 2016

Questions:

1. Starvation is a state when a thread does not get the access to a certain resource, because other threads get the access to the resource repeatedly and hence the process might wait indefinately. The given protocol (if the deadlock does not arise and all processes have same priority) is starvation free because every time when the process is busy waiting in the inner loop it update the turn as me. This allows all the threads equal chance to acquire lock ones its freed by the previous thread.

2. Deadlock is a state when the threads/processes hold on some resource and wait on the resource held by the other process, thus none of them makes progress. This protocol is NOT DEADLOCK free. There can be a situation when a process is context switch due to timer interrupt right after it sets busy to true, but before checking the while condition and exiting the loop. In that case busy would be set to true and 
