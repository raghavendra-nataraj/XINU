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
