The program implements Inter Process Communication via shared memory mechanism. Two process- write_process and read_process- are created. The write_process initializes the shared a memory by shmget and writes the message to that shared memory. The read_process gets the id of the shared memory by shmget and reads from there.

The following system calls were implemented:
1. shmget
2. shmat
3. shmdt

shmget.c - 
It creates a new shared memory if the flag is SHM_EXIST or SHM_CREATE of the given size using getmem and makes an entry in shmtab associated with the given key. If the flag is SHM_CREATE and their is an existing entry associated with the given key, it generates an error. If the flag is SHM_EXIST it returns the id of existing memory if it does exist else creates a new entry in shmtab and returns its id.

shmat.c - 
It attaches the shared memory segment identified by shmid to the address space of the calling process. If the shmaddr specifies the address, it attaches the memory to that address else it uses some unused address and attach it there.

shmdt.c - 
It invalidates the entry from shmtab associated with the given key and frees the memory using freemem.


Questions:

1. Freebuf is more efficient than freemem. In case of freebuf the pool ID stored in four bytes preceding the buffer address is used to locate the entry in table of buffer pool, which then links the buffer back to free pool. Whereas in case of freemem, the list is searched until the address of the block to be returned lies between prev and next. It combines the new block with adjacent block to form one large block on the free list by coalesing it with previous and next block. 
