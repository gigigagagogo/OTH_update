#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	//Il processo padre va a creare un processo figlio, ora ne abbiamo 2 processi in totale
	fork();
	//I 2 processi vanno a creare ciascuno un procoesso quindi in totale 4 processi
	fork();
	//i 4 processi " " 8 processi
	fork();
	//Ognuno dei 8 processi andrà ad eseguire il print
	printf("Hello world!\n");
	return 0;
}
