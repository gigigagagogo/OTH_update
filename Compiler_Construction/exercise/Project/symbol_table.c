#include "types.h"

void print_all_scopes(Scope *scope) {
    int level = 0;
    while (scope) {
        printf("Scope Level %d:\n", level);
        print_symbol_table(scope->symbolTable);
        scope = scope->parent;
        level++;
    }
}


void print_symbol_table(ht_str *symbolTable) {
    if (!symbolTable) {
        printf("Symbol table is NULL\n");
        return;
    }

    printf("\nSymbol Table:\n");
    printf("===============================\n");

    for (int i = 0; i < symbolTable->size; i++) {
        Node *current = symbolTable->entries[i];
        while (current) {
            printf("Key: %s, Type: %d, Value: ", current->key, current->value.type);

            switch (current->value.type) {
                case 0:
                    printf("%d\n", current->value.u.i);
                    break;
                case 1:
                    printf("%f\n", current->value.u.d);
                    break;
                case 2:
                    printf("\"%s\"\n", current->value.u.s);
                    break;
                case _LIST_TYPE:
                    printf("List (capacity: %d, size: %d)\n",
                           current->value.u.list->capacity, current->value.u.list->size);
                    break;
                default:
                    printf("Unknown or unsupported type\n");
                    break;
            }
            current = current->next;
        }
    }

    printf("===============================\n");
}


void free_ht (ht_str *hashtable) {
    if (hashtable == NULL) {
        return; 
    }

    for (int i = 0; i < hashtable->size; i++) {
        Node *current = hashtable->entries[i];
        while (current != NULL) {
            Node *temp = current; 
            current = current->next; 

            free(temp->key);

            if (temp->value.type == 2) {
                free(temp->value.u.s);
            }

            free(temp);
        }
    }

    free(hashtable->entries);

    free(hashtable);
}


void resize_table (ht_str *hashtable) {
    int new_size = hashtable->size * 2; 
    Node **new_entries = malloc(sizeof(Node *) * new_size);

    if (!new_entries) {
        printf("Error: Memory allocation failed during resize!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < new_size; i++) {
        new_entries[i] = NULL;
    }

    for (int i = 0; i < hashtable->size; i++) {
        Node *current = hashtable->entries[i];
        while (current) {
            unsigned int new_index = hash_function(current->key, new_size);

            Node *new_node = malloc(sizeof(Node));
            new_node->key = strdup(current->key);
            new_node->value = current->value;
            new_node->next = new_entries[new_index];
            new_entries[new_index] = new_node;

            Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp); 
        }
    }

    free(hashtable->entries);
    hashtable->entries = new_entries;
    hashtable->size = new_size;
}


value_t *search (ht_str *hashtable, const char *key){
	static value_t not_found = { .type = -1 };
	unsigned int index = hash_function(key, hashtable->size);

	Node *entry = hashtable->entries[index];
	
	if(entry == NULL){
		return &not_found;
	}

	while(entry != NULL){
		if(strcmp(entry->key, key) == 0){
			return &entry->value;
		}
		entry = entry->next;
	}

	return &not_found;


}

Node *ht_pair(const char *key, const value_t value) {
	Node *entry = malloc(sizeof(Node));
	entry->key = malloc(strlen(key) + 1);
	entry->value =value;

	strcpy(entry->key, key);
	entry->value = value;

	entry->next = NULL;

	return entry;
}


void ht_set (ht_str *hashtable, const char *key, const value_t value){
	//check for 75%	
	if (hashtable->count >= (hashtable->size * 0.75)) {
        	resize_table(hashtable);
    	}

	unsigned int index = hash_function(key, hashtable->size);
	
	Node *currentBucket = hashtable->entries[index];

	if(currentBucket == NULL){
		hashtable->entries[index] = ht_pair(key, value);
		return;
	}
	
	Node *prev;

	while(currentBucket != NULL){
		if(strcmp(currentBucket->key, key) == 0){
			if(currentBucket->value.type == 2){
				free(currentBucket->value.u.s);
			}
			currentBucket->value = value;
			return;
		}
		prev = currentBucket;
		currentBucket = prev -> next;
	}

	prev->next = ht_pair(key, value);	
	hashtable->count++;
}

unsigned int hash_function (const char *key, int size){
	unsigned long int hash = 0;

	while(*key){
		hash = hash *37 + *key++;
	}

	return (hash % size);
}

ht_str *create_ht (int size){
	ht_str *hashtable = malloc(sizeof(ht_str) * 1);

	hashtable->entries = malloc(sizeof(Node *) * size);

	if(!hashtable->entries){
		printf("Error memory allocation!");
		exit(EXIT_FAILURE);
	}

	hashtable->size = size;
	hashtable->count = 0;

	for(int i = 0; i < size; i++){
		hashtable->entries[i] = NULL;
	}

	return hashtable;
}

