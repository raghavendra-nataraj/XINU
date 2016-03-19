Part 1
The program implements Inter Process Communication via shared memory mechanism. Two process- write_process and read_process- are created. The write_process initializes the shared a memory by shmget and writes the message to that shared memory. The read_process gets the id of the shared memory by shmget and reads from there. We also made some changes in initialize.c to initialize the shared memory table- shmtab, which is an array of shment of size NSHMENT. shment consist of key, refcount, size and shmemory.

The following system calls were implemented:
1. shmget
2. shmat
3. shmdt

shmget.c
It creates a new shared memory if the flag is SHM_EXIST or SHM_CREATE of the given size using getmem and makes an entry in shmtab associated with the given key. If the flag is SHM_CREATE and their is an existing entry associated with the given key, it generates an error. If the flag is SHM_EXIST it returns the id of existing memory if it does exist else creates a new entry in shmtab and returns its id.

shmat.c
It attaches the shared memory segment identified by shmid to the address space of the calling process. If the shmaddr specifies the address, it attaches the memory to that address else it uses some unused address and attach it there.

shmdt.c
It invalidates the entry from shmtab associated with the given key and frees the memory using freemem.


Part 2
The program perform three types of Inter Process Communication - shared memory, pipe, files. Program is forked in two -leader(parent) and follower(child). The sychronization is done via named semaphores. The data to be written to the file is created and the numbers iterated are appended to the char buffer.

It consists of following files:
1.ipc_bench.h
2.ipc_bench.c
3.leader.c
4.follower.c
5.helper.c


File :
The leader process first creates the file in the temp folder and then writes the data created to that file. The follower process is then signaled to start reading and then verify the data. Once the data is verified follower creates the data to be wriiten to the file and signals the leader to read after writing onto the file. The data is read and verified on the leader side as well and the whole process is repeated nine more times. The biderectional read and write is timed (excluding verification part) and the average time per iteration is calculated at the end and printed by the leader(parent) process.

Shared Memory :
The shared memory is created before the program is forked and key is the global variable set before forking. The leader process first gets the reference ID of the shared memory and then writes the data created to the memory. The follower process is then signaled to start reading and then verify the data. Once the data is verified, follower creates the data to be wriiten to the memory and signals the leader to read after writing. The data is read and verified on the leader side as well and the whole process is repeated nine more times. The biderectional read and write is timed (excluding verification part) and the average time per iteration is calculated at the end and printed by the leader(parent) process.

Pipes :
The single pipe is created before the program is forked and key is the global variable set before forking. The leader process creates the data and writes to the pipe.Simultaneously the follower process starts reading and then verify the data. Once the data is verified, follower creates the data to be wriiten to the memory and signals the leader to read after writing. The data is read and verified on the leader side as well and the whole process is repeated nine more times.The reading of data includes a select statement which times out of read to identify the end of data in buffer. The biderectional read and write is timed (excluding verification part) and the average time per iteration is calculated at the end and printed by the leader(parent) process.

Annalysis :

Per iteration time taken to complete bidirectional tranfer of 4MiB data (excluding verification) is:
1. File = 21155635 nsec
2. Shared Memory = 17347642 nsec
3. Pipes = 25970459 nsec

Thus we can conclude Shared Memory is the fastest method of Inter Process Communication and Pipes is the slowest (almost double).

Questions:

1. Freebuf is more efficient than freemem in terms of performance (execution time). In case of freebuf the pool ID stored in four bytes preceding the buffer address is used to locate the entry in table of buffer pool, which then links the buffer back to free pool. Whereas in case of freemem, the list is searched until the address of the block to be returned lies between prev and next. Then it combines the new block with adjacent blocks to form one large block on the free list by coalesing it with previous and next block. This coalesing takes more time. But, in case of memory allocation (not buffer allocation) freemem is the most efficient in terms of memory management, since it does coalesing and one large chunk of memory is available after coalesing.

2. The underlying Address translation hardware converts the virtual address to physical address. When the process refers to address 'd', it will be mapped to the memory location that corresponds to 'd' in that process' memory location. Since the hardware maps only the virtual address to specific region in memory it wont allow the process to access other process' stack accidently accidently. 


Contribution :
We split the work into half and then did the debugging and testing together. For the questions we discussed the answers and submit the unanimous answer.  
