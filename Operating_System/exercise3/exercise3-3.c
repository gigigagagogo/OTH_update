#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
	pid_t r = fork();
	//Se ritorna un valore negativo (di solito -1) significa che ha prodotto un errore
	if (r < 0)
		printf("Child process could not be created.");
	if (r > 0) {
		//Il metodo fork ritorna il pid del figlio 
		printf("I am the parent process. Fork has returned: \%i\n", r);
		pid_t m = getpid();
		//Questo è il pid del processo chiamante (in questo caso il padre), vengono creati in modo sequenziale
		printf("I am the parent process. My pid is: \%i\n", m);
	}
	if (r == 0) {
		//Qui restituisce 0 perché consente al processo figlio di sapere che è un processo appena creato
		printf("I am the child process. Fork has returned: \%i\n", r);
		pid_t m = getpid();
		printf("I am the child process. My pid is: \%i\n", m);
	}
}
