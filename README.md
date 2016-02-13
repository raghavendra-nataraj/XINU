# Spring 2016

Q1. This behaviour is called deadlock.

Q2. The program creates 4 process. Due to the I/O inturupt first process is swaped before executing all the statements in that loop.Now lets consider the case with input as 4. Here for the first round value goes as 20 -> 19 -> 18 -> 17. But, after that in second round the variable 'Count' (which is a global variable) gets decremented, but the context switch happens due to system call (kprintf) before it could be written to the inbox of next process. Since, there is no explicit sychronization implemented the next process starts executing and uses the previous value in its inbox and updates the 'Count' with that value. Hence it never reaches 0 and does not exit the loop. 

Q3. The program prints out of order in all the cases but the correct one. This is because in all other case the process writes in the inbox of next process before the system call (kprintf) and thus when the context switch happens the next process also eneters the if condition. Now we have multiple process excuting the same piece of code and competing for I/O. Since it is not possible to determine how the scheduling works the output is printed out of order. This is called 'Race' condition.

Q4. In the correct working version of the program the system call happens right after the process enters the 'if' condition. Now since, the process has not updated the 'count' variable nor has it written anything in the inbox of the next process, therefore next process is not able to execute 'if' block and is busy waiting for previous process to update. Since XINU always schedule processes in the fifo order. The control is passed in a synchronous manner and hence program runs correctly.


Contribution of Each team member.

We discussed on the logic and then decided to first code our own versions of whole program (since it was not a lengthy code). Since we came up with very similar approach we decided to stick with one of the code and modified it together (peer programming). Then we discussed the answers to the questions and split the answers (2-2).
