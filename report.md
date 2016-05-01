Implementation

There is a member "prdesc" which is a array in the process entry for each process. It holds the devices opened initially (stdin.stdout,stderr). We have extended the implementation to add the file opens to "prdesc" array. the total number of opened files is stored in  prdescNum. When a file is closed manualy by user this array value for index corresponding to the file is updated to -1. When the process is closed all the values which are not -1 are closed automatically.


Files modified
process.h
open.c
kill.c
close.c

A new file xsh_testFS is added to test this feature. In the file multiple files are open and one is closed . At the end of execution it prints all the file that are not closed. 

Note : i have increased the NDESC to 9 (initially it was 5) to test opening and closing more files.



Answer 

  1 disk block = 7 Index nodes
  1 Index Node = 16 data block pointers
  Total Number of disc blocks = n
  Total number of files in directory = k
  
  Number of Index node to store 1 file in directory = [1/16]    ->  where [] repreents ceil
  Number of Disc block to store K files in directory = [k/(16*7)]
  
  Number of Index node to store data for a file = [x/16]   -> x is the number of data blocks occupied by file contents 
  Number of Disk Block to store data for a file = [x/(16*7)]
  Number of Disk Block to store data for k files = i=1 to k :sum([x(i)/(16*7)])
  
  so 
  
  n = num_dir_block + num_file_block + num_data_block
  
  Number of Index Block = num_dir_block + num_file_block
  
  where 
    num_dir_block = [k/(16*7)]
    num_file_block = i=1 to k : sum[x(i)/(16*7)]
    num_data_block =  i=1 to k : sum(x(i))
