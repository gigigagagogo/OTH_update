#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t r = fork();
    pid_t w;

    if (r < 0) {
        printf("Child process could not be created.\n");
    } else if (r > 0) {
        // Processo padre
        printf("I am the parent process. Fork has returned: %d\n", r);
        pid_t m = getpid();
        printf("I am the parent process. My pid is: %d\n", m);
        pid_t mm = getppid();
        printf("The parent process of %d is: %d\n", m, mm);

        // Attendere il termine del processo figlio
        w = wait(NULL);
        if (w == r)
            printf("Parent process: Child with pid %i is done\n", w);
    } else {
        // Processo figlio
        printf("I am the child process. Fork has returned: %d\n", r);
        pid_t m = getpid();
        printf("I am the child process. My pid is: %d\n", m);
        sleep(3); // Ritarda il figlio per dimostrare la differenza
        pid_t mm = getppid();
        printf("The parent process of %d is: %d\n", m, mm);
    }

    return 0;
}

