#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<unistd.h>
int main() {
    pid_t r = fork();
    if (r < 0)
        printf("Child process could not be created.\n");
    if (r > 0) {
        printf("I am the parent process. Fork has returned: %d\n", r);
        pid_t m = getpid();
        printf("I am the parent process. My pid is: %d\n", m);
        pid_t mm = getppid();
        printf("The parent process of %d is: %d\n", m, mm);
    }
    if (r == 0) {
        printf("I am the child process. Fork has returned: %d\n", r);
        pid_t m = getpid();
        printf("I am the child process. My pid is: %d\n", m);
        //Il processo padre termina prima di che termini il processo figlio quindi al figlio viene assegnato un altro
	//padre (il processo init (PID = 1) o il processo systemd (PID = 1665))
	sleep(3);
	pid_t mm = getppid();
        printf("The parent process of %d is: %d\n", m, mm);
    }

    return 0;
}

