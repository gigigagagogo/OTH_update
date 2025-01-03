#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grammar.h"
#include "queue.h"
#include "util.h"

void generate_words(node_g *head, char *startSymbol){
	node_t *wordQueueHead = NULL, *wordQueueTail = NULL;
	enqueue_word(&wordQueueHead, &wordQueueTail, startSymbol);

	while(!emptyqueue(&wordQueueHead)){
		char *currentWord=dequeue_word(&wordQueueHead, &wordQueueTail);
		printf("Word: %s\n", currentWord);
		
		if(!isterminal(currentWord)){
			node_g *ruleNode=head;

			while(ruleNode != NULL){
				
				int n=0;
			       	char *newWord = NULL;
				do{
					
					newWord = rep(currentWord, ruleNode -> rule.lhs, ruleNode -> rule.rhs, n++);
					if(newWord != NULL){
						enqueue_word(&wordQueueHead, &wordQueueTail, newWord);
					
					}
				}while(newWord);
			ruleNode = ruleNode -> next;
			}
		}else{
			printf("Word contains only terminate symbol: %s\n", currentWord);
		}
		free(currentWord);
	}
}


int main(void){
	node_g *head = NULL;
	node_g *tail = NULL;

	if(generate_rules(&head,&tail) != 0){
		printf("Error with rules generation!\n");
		return 1;
	}
	
	print_rules(head);

	char *startSymbol = STARTSYMBOL;

	generate_words(head, startSymbol);

	return 0; 

}
