#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void *getFile(void *arg);
int fileCount;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int totalTime = 0;

void sigHandler (int sigNum) {
    	printf ("\nNumber of requests: %d\n", fileCount);
    	printf ("\nTotal time: %d\n", fileCount);
    	printf ("\nAverage file request time: %f\n", totalTime / (float)fileCount);
    	exit(0);
}

void *getFile(void *arg){
	char *file = (char *)arg;
	printf("\nRetrieving file: %s\n", file);

	int rand1 = (rand() % (10)) + 1;
    	int sleepTime;
    	if(rand1 < 9)
        	sleepTime = 1;
    	else
        	sleepTime = (rand() % (4)) + 7;
    		sleep(sleepTime);

    	int mStatus = pthread_mutex_lock(&mutex);
    	if(mStatus != 0) {
        	printf("mutex failed to lock\n");
        	exit(2);
    	}

    	//shared data protected with mutex
    	totalTime += sleepTime;

    	mStatus = pthread_mutex_unlock(&mutex);
    	if(mStatus != 0) {
        	printf("mutex failed to unlock\n");
        	exit(3);
    	}
	if(sleepTime > 1){
		printf("Failed to retrieve file");
	}else{
		printf("\nFile %s retrieved successfully. Closing thread.\n", file);
    	}
	free(file);
	return 0;
}

int main(){
	int status;
    	signal (SIGINT, sigHandler);

	while(1){
        char *filename = malloc(20);
		printf("Name of file to retrieve: ");
		scanf("%s", filename);
	   	pthread_t thread;
		status = pthread_create(&thread, NULL, getFile, filename);
		if(status != 0){
			fprintf(stderr, "thread create error %d: %s\n", status, strerror(status));
	    		exit(1);
            		free(filename);
		}
        //makes the thread die when done
        pthread_detach(thread);
        fileCount++;
	}
}


