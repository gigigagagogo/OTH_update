#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
	int a = 42;
	printf("%d\n", a);
	pid_t r = fork();
	if (r < 0) {
		printf("Child process could not be created");
	}
	if (r > 0) {
		a = a + 10;
		printf("Parent: %d\n", a);
		printf("I am the parent process. Fork returns: %i\n", r);
	}
	if (r == 0) {
		a = a + 20;
		printf("Child: %d\n", a);
		printf("I am the child process. Fork returns: %i\n", r);
	}
}
