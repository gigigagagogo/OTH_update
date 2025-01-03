#include <stdio.h>
#include <stdlib.h>

typedef int val_t;

typedef struct node{
	val_t *valore;
	struct node *next;
}node_s;

void s_push(node_s **head, val_t data){
	node_s *newNode = malloc(sizeof(node_s));
	
	if(newNode == NULL){
		printf("Error with memory allocation!\n");
		exit(-1);
	}
	newNode -> valore = malloc(sizeof(val_t));
	
	if ((newNode -> valore) == NULL){
		printf("Error with memory allocation!\n");
		free(newNode);
		exit(-1);
	}

	*(newNode -> valore) = data;
	
	newNode -> next = *head;

	*head = newNode;
	
}

val_t s_pop(node_s **head){
	node_s *temp = *head;

	if(temp == NULL){
		printf("Error with memory allocation!\n");
		exit(-1);
	}
	val_t record = *(temp -> valore);
	
	if(temp == NULL){
		*head = NULL;
	}else{
		*head = temp -> next;
	}
	free(temp -> valore);
	free(temp);
	return record;
}

int s_empty(node_s **head){
	return (*head == NULL);
}

void print_all(node_s *head){

	while(!s_empty(&head)){
		printf("%d\n", *(head -> valore));
		head = head -> next;
	}

}

int main(void){
	node_s *head = NULL;

	s_push(&head, 3);
	s_push(&head, 2);
	s_push(&head, 4);
	s_push(&head, 7);
	s_push(&head, 3);
	
	s_pop(&head);
	s_pop(&head);

	print_all(head);

	return 0;

} 
