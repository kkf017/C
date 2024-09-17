#include <stdio.h>
#include <stdlib.h>

#include "LIST.h"


// https://stackoverflow.com/questions/38018716/pointer-as-a-parameter-in-c


/********* MAIN TEST **********************
void func(){
	TElement* stack = NULL;
	push(&stack, 7);
	push(&stack,11);
	push(&stack,3);
	display(&stack);
	
	int value = pop(&stack,11);
	printf("\n\nValue: %d", value);
	display(&stack);

	clear(&stack);
}
**********************************************/

void push(TElement **first,int n){

	TElement *new = malloc(sizeof(TElement));
	
	if(new == NULL){
		exit(EXIT_FAILURE);
	}
	
	new->element = n;
	new->next = NULL;
	
	new->next = *first;
	*first = new;

}//end insert


int pop(TElement **first, int n){
	TElement *actual = *first;
	
	while(actual->next->element != n){
		actual = actual->next;
	}
	
	int value = actual->next->element;
	TElement *delete = actual->next;
	actual->next = actual->next->next;
	
	free(delete);
	
	return value;	
}//end delete

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

