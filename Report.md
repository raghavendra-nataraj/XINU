============
Working :
============
The program works on "Busy Waiting". Two global valatile variables count and inbox[] are declared. The count variable is decremented in each process. The count variable before decrementing is the same value as the inbox value of the current process. The entry condition to each process to print is based on the remainder of the count when divided by NUM_PROCESSES. The reminder will have to be equal to any of the process ID. So only when it is equal the process is valid to print, otherwise it is in "Busy Waiting" state.

Output :-
xsh $ process_ring 3
Ring Element 0 : Round 0 : Value : 12
Ring Element 1 : Round 0 : Value : 11
Ring Element 2 : Round 0 : Value : 10
Ring Element 3 : Round 0 :xsh $  Value : 9
Ring Element 0 : Round 1 : Value : 8
Ring Element 1 : Round 1 : Value : 7
Ring Element 2 : Round 1 : Value : 6
Ring Element 3 : Round 1 : Value : 5
Ring Element 0 : Round 2 : Value : 4
Ring Element 1 : Round 2 : Value : 3
Ring Element 2 : Round 2 : Value : 2
Ring Element 3 : Round 2 : Value : 1
Zero!!

The primary differnce between the correct working program and other programs is we have used is count and the inbox of current process interchageably.
Also the statement inside the loop are altered its position before and after the printf(system call).

===============
Wrong Order 
===============

In this we just pushed the assignment statement(inbox of next process with count -1 value) before the print(system call) statement.

Output :-
xsh $ process_ring 3
Ring Element 0 : Round 0 : Value : 12
Ring Element 1 : Round 0 : Value : 11
Ring Element 2 : Round 0 : Value : 10
Ring Element 3 : Round 0 :xsh $ Ring Element 0 : RoRing Element 1 : Round 1 Ring Element 2 : Round 1  Value : 9
Ring Elementund 1 : Value : 8
Ring E: Value : 7
Ring Element: Value : 6
Ring Element 3 : Round 1 : Value : 5
                                    lement 0 : Round 2 : Valu 1 : Round 2 : Value : 3 2 : Round 2 : Value : 2
Ring Element 3 : Round 2e : 4
Zero!!
 : Value : 1

=============
Infinite :-
=============
The infinite is achieved by replacing the count variable by inbox value.

============
DeadLock :-
============
In deadlock we introduce a redundant statement where we assign the count to inbox of same process(The values are same however).The output also has a "ps" command output which displays the current running process. Where the "i" has four running process which is created by the program.

Output:-

xsh $ process_ring 4
Ring Element 0 : Round 0 : Value : 16
Ring Element 0 : Round 1 : Value : 15
xsh $ ps
Pid Name             State Prio Ppid Stack Base Stack Ptr  Stack Size
--- ---------------- ----- ---- ---- ---------- ---------- ----------
  0 prnull           ready    0    0 0x9FFFFFFC 0x9FFFFF44     8192
  1 rdsproc          wait   200    0 0x9FFFDFFC 0x9FFFDAF0    16384
  2 Main process     recv    20    0 0x9FFF9FFC 0x9FFF9F70    65536
  3 ipout            wait   500    2 0x9FFE9FFC 0x9FFE9F90     8192
  4 netin            wait   500    2 0x9FFE7FFC 0x9FFE7F58     8192
  5 shell            recv    50    2 0x9FFE5FFC 0x9FFE5C98     8192
  7 i                ready   20    6 0x9FFE1FFC 0x9FFE1F48     1024
  8 i                ready   20    6 0x9FFE1BFC 0x9FFE1B48     1024
  9 i                ready   20    6 0x9FFE17FC 0x9FFE1748     1024
 10 i                ready   20    6 0x9FFE13FC 0x9FFE1348     1024
 11 ps 

===================================================================
			Question Section
===================================================================
Q1. Why does your program hang? What is the name of this behavior?

This behaviour is achieved by changing the entry condition inside loop by replacing the count variable with inbox variable and adding a redundant line in the loop. At the begining of each loop the count variable and the inbox of the current process is same. We add a statement to assign count to inbox of current process. In a synchronous behavior this will not have any effect. However in an asynchronour behaviour, the context switch happens due to system call(printf) before the count variable is decremented. So this will assign the same count value to the inbox. This makes it void of entry into the "if" condition. The same happens for all four processes and all the loops become "busy waiting".This behaviour is called deadlock.

Q2. Why does your program go into an infinite loop? What is the name of this behavior?

The program creates 4 process. Due to the I/O inturupt first process is swaped before executing all the statements in that loop.Now lets consider the case with input as 4. Here for the first round value goes as 20 -> 19 -> 18 -> 17. But, after that in second round the variable 'Count' (which is a global variable) gets decremented, but the context switch happens due to system call (kprintf) before it could be written to the inbox of next process. Since, there is no explicit sychronization implemented the next process starts executing and uses the previous value in its inbox and updates the 'Count' with that value. Hence it never reaches 0 and does not exit the loop. This is called unbounded context switching.

Q3. Why does your program print numbers out of order? What is the name of this behavior?

The program prints out of order in all the cases but the correct one. This is because in all other case the process writes in the inbox of next process before the system call (kprintf) and thus when the context switch happens the next process also eneters the if condition. Now we have multiple process excuting the same piece of code and competing for I/O. Since it is not possible to determine how the scheduling works the output is printed out of order. This is called 'Race' condition.

Q4. What property of Xinu allows the working version of your program to print values in the correct order?

In the correct working version of the program the system call happens right after the process enters the 'if' condition. Now since, the process has not updated the 'count' variable nor has it written anything in the inbox of the next process, therefore next process is not able to execute 'if' block and is busy waiting for previous process to update. Since XINU always schedule processes in the fifo order. The control is passed in a synchronous manner and hence program runs correctly.

Contribution of Each team member.

We discussed on the logic and then decided to first code our own versions of whole program (since it was not a lengthy code). Since we came up with very similar approach we decided to stick with one of the code and modified it together (peer programming). Then we discussed the answers to the questions and split the answers (2-2).
