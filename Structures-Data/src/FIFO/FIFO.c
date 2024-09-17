#include <stdio.h>
#include <stdlib.h>

#include "FIFO.h"


/********* MAIN TEST **********************
void func(){
	TElement* stack = NULL;
	push(&stack, 7);
	push(&stack,11);
	push(&stack,3);
	display(&stack);
	
	int value = pop(&stack);
	printf("\n\nValue: %d", value);
	display(&stack);

	clear(&stack);
}
**********************************************/

void push(TElement** first, int n){
	TElement *new = malloc(sizeof(TElement));
	
	if(new == NULL){
		exit(EXIT_FAILURE);
	}
	
	new->element = n;
	new->next = NULL;
	
	new->next = *first;
	*first = new;
}//end push

int pop(TElement** first){
	TElement *actual = *first;
	
	TElement *delete = actual;
	
	int value = actual->element;
	*first = (*first)->next;
	
	free(delete);
	
	return value;
		
}//end pop



void clear(TElement **first){
	TElement *actual = *first;
	
	if(*first == NULL){
		exit(EXIT_FAILURE);
	}
	
	while(actual->next != NULL){
		TElement *delete = actual;
		actual = actual->next;
		free(delete);		
	}
		
	TElement *delete = actual;
	actual = NULL;
	free(delete);	
	
}//end clear


void display(TElement **first){
	TElement *actual = *first;
	
	if(*first == NULL){
		exit(EXIT_FAILURE);
	}
	
	printf("%s", "\n");
	while(actual != NULL){
		printf("\nElement: %d", actual->element);
		actual = actual->next;
	}
}//end display
