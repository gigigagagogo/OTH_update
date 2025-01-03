#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void* ourthread (void *arg);
int a = 42;
int main() {
	pthread_t th[2];
	int i;
	printf("Before thread creation, the value of variable a is: %i\n",a);
	for (i = 0; i < 2; i++) {
		if(pthread_create(&th[i], NULL, ourthread, NULL) != 0) {
			printf("Thread could not be created. \n");
		}
	}
	for (i = 0; i < 2; i++) {
		pthread_join(th[i], NULL);
		printf("%i. Thread is done\n",i+1);
	}
	printf("After thread creation, the value of variable a is: %i\n", a);
	exit(0);
}
void* ourthread (void *arg){
	a = a+30;
	printf("Thread with ID %ld computes a +30. The value of variable a within the thread: %i\n", (unsigned long)pthread_self(),a);
	return &a;
}
