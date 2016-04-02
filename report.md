In this assignment we have implemented system calls future_alloc,future_get, future_set and future_free. The program creates three instances of futures with mode set to EXCLUSIVE, SHARED and QUEUE respectively. The respective future is passed as an argument to the new processes, future_prod and future_cons. The future_prod set the value using future_set and future_cons get the value using future_get.

1. future_alloc : Creates a new future instance by allocating memeory using getmem and returns the pointer to it. It sets the following - 
future_obj->mode = the mode passed as an argument,
future_obj->state = FUTURE_EMPTY,
future_obj->pid = 0,
future_obj->set_queue = creates a new queue and set it to qid,
future_obj->get_queue = creates a new queue and set it to qid.

2. future_get : It gets the future value which is already set by future_set. If the state is alread FUTURE_EMPTY or FUTURE_WAITING, it gets its pid, enque itself to the get_queue and suspends. It sets the state to FUTURE_WAITING and if the state is FUTURE_VALID it also dequeues one process from the set_queue and resumes it. It sets the value argument to the value set by future_get.

3. future_set : It sets the value field in future to the value passed as argument to the future_set system call and sets mode to FUTURE_VALID. If the state is FUTURE_VALID it throws error in case of EXCLUSIVE and SHARED (because only one call to future_set is allowed in that case), else it gets its pid, enqueues itself to set_queue and suspends.In case state is FUTURE_EMPTY or FUTURE_WAITING, it enqueues itself to set_queue if the get_queue is empty and suspends. Otherwise it dequeues single process from the get_queue if mode is QUEUE, else all the processes if mode is EXCLUSIVE (will only have one process in the queue) or SHARED.

4. future_free : It frees the memory allocated to future object using freemem.
