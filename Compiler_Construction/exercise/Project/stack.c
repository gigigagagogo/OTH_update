#include <stdio.h>
#include <stdlib.h>
#include "types.h"


void s_push(node_s **head, value_t data){
	node_s *newNode = calloc(1, sizeof(node_s));
	
	if(newNode == NULL){
		printf("Error with memory allocation!\n");
		exit(EXIT_FAILURE);
	}
	if(data.type == 2){
		newNode->val.type = 2;
		newNode->val.u.s = strdup(data.u.s);
	}else{
		newNode -> val = data;
	}
		
	newNode -> next = *head;

	*head = newNode;
	
}

value_t s_pop(node_s **head){
	node_s *temp = *head;

	if(temp == NULL){
		printf("Error with memory allocation!\n");
		exit(-1);
	}
	value_t record = temp -> val;
	
	if(temp == NULL){
		*head = NULL;
	}else{
		*head = temp -> next;
	}
	free(temp);
	return record;
}

int s_empty(node_s **head){
	return (*head == NULL);
}
/*
void print_all(node_s *head){

	while(!s_empty(&head)){
		printf("%d\n", head -> val);
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
*/
