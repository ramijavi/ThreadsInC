# ThreadsInC by Javier Ramirez & Eric Darr
This mini-programming assignment simulates the thread execution manifested by a fileserver process.

Develop a multi-threaded program with the following specifications:

The Dispatch thread should:

* input a string from the user (simulating the name of a file to access)
* spawn a worker thread and communicate to it the filename entered by the user
* immediately repeat the input/spawn sequence (i.e. prepare to accept a new file request)

Each Worker thread should:
* obtain the simulated filename from the dispatcher
* sleep for a certain amount of time, simulating the time spent performing a file access:
    * with 80% probability, sleep for 1 second. This simulates the scenario that the Worker thread has found the desired file in the disk cache and serves it up quickly.
    * with 20% probability, sleep for 7-10 seconds (randomly). This simulates the scenario that the worker thread has not found the requested file in the disk cache and must wait while it is read in from the hard drive.
wake up, print a diagnostic message that includes the name of the file accessed, terminate

Your program should continue to execute until terminated by the user (^C).  At that point, your program should print out basic statistics
total number of file requests received/serviced
When terminated, your program should cleanup as appropriate and shutdown gracefully.

In addition to being correct, your program should be efficient and should execute in parallel. Remember that threads share data -- as a rule, all multi-threaded programs should be carefully scrutinized for potential race conditions or "data clobbering".
