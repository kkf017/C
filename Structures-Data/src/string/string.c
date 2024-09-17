#include <stdio.h>
#include <stdlib.h>

#include <string.h>


/********* MAIN TEST **********************
void func(){
	char *str = "Hello, L.";
    	//printf("%s", str);
    	
    	char *newstr = String(&str, 6);
    	printf("\nnew str: %s", newstr);
    	
    	clear(&newstr);
    	
    	
    	char tabStr[MAXSTR] = "Hello, L.";
    	displayTest(&tabStr[0]);
}
**********************************************/

char * String(char **str, int size){

	char *newStr = (char *)malloc(sizeof(char)*size);
	
	//char *fillStr = newStr;
	for (int i=0; i<size-1; i++){
		*(newStr+i) = (*str)[i];
	}
	*(newStr+(size-1)) = '\0';
	
	//printf("%s", newStr);

	return newStr;
	
}


void displayTest(char *str){
	int i = 0;
	while(*(str+i) != '\0'){
		printf("%c", *(str+i));
		i++;
	}
}


char * clear(char **str){
	free(*str);
	*str = NULL;
}
