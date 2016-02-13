# Spring 2016

Working : 

The program works on "Busy Waiting". Two global valatile variables count and inbox[] are declared. The count variable is decremented in each process. The count variable before decrementing is the same value as the inbox value of the current process. The entry condition to each process to print is based on the remainder of the count when divided by NUM_PROCESSES. The reminder will have to be equal to any of the process ID. So only when it is equal the process is valid to print, otherwise it is in "Busy Waiting" state.

    Why does your program hang? What is the name of this behavior?

Q1. This behaviour is achieved by changing the entry condition inside loop by replacing the count variable with inbox variable and adding a redundant line in the loop. At the begining of each loop the count variable and the inbox of the current process is same. We add a statement to assign count to inbox of current process. In a synchronous behavior this will not have any effect. However in an asynchronour behaviour, the context switch happens due to system call(printf) before the count variable is decremented. So this will assign the same count value to the inbox. This makes it void of entry into the "if" condition. The same happens for all four processes and all the loops become "busy waiting".This behaviour is called deadlock.

    Why does your program go into an infinite loop? What is the name of this behavior?

Q2. The program creates 4 process. Due to the I/O inturupt first process is swaped before executing all the statements in that loop.Now lets consider the case with input as 4. Here for the first round value goes as 20 -> 19 -> 18 -> 17. But, after that in second round the variable 'Count' (which is a global variable) gets decremented, but the context switch happens due to system call (kprintf) before it could be written to the inbox of next process. Since, there is no explicit sychronization implemented the next process starts executing and uses the previous value in its inbox and updates the 'Count' with that value. Hence it never reaches 0 and does not exit the loop. 

    Why does your program print numbers out of order? What is the name of this behavior?

Q3. The program prints out of order in all the cases but the correct one. This is because in all other case the process writes in the inbox of next process before the system call (kprintf) and thus when the context switch happens the next process also eneters the if condition. Now we have multiple process excuting the same piece of code and competing for I/O. Since it is not possible to determine how the scheduling works the output is printed out of order. This is called 'Race' condition.

    What property of Xinu allows the working version of your program to print values in the correct order?
Q4. In the correct working version of the program the system call happens right after the process enters the 'if' condition. Now since, the process has not updated the 'count' variable nor has it written anything in the inbox of the next process, therefore next process is not able to execute 'if' block and is busy waiting for previous process to update. Since XINU always schedule processes in the fifo order. The control is passed in a synchronous manner and hence program runs correctly.


Contribution of Each team member.

We discussed on the logic and then decided to first code our own versions of whole program (since it was not a lengthy code). Since we came up with very similar approach we decided to stick with one of the code and modified it together (peer programming). Then we discussed the answers to the questions and split the answers (2-2).
