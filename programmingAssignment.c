#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void *getFile(void *arg);
int fileCount;
char filename[20];

int main(){

	pthread_t thread;
	int status;

	while(1){
		printf("Name of file to retrieve: ");
		scanf("%s", filename);
		printf("\n");
		status = pthread_create(&thread, NULL, getFile, &filename);
		if(status != 0){
			fprintf(stderr, "thread create error %d: %s\n", status, strerror(status));
	    		exit(1);
		}
	}
}

void *getFile(void *arg){
	char *file = (char *)arg;
	printf("Retrieving file: %c\n", *file);
	return NULL;
}
