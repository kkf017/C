#include <stdio.h>
#include <stdlib.h>

//#include <Read.h>


/********* MAIN TEST **********************
void func(){
	
}
**********************************************/


void read(char *filename){

	FILE *fptr = fopen(filename, "r"); 

	if(fptr == NULL) {
	  printf("Not able to open the file."); /// error, sys.exit(EXIT_FAILURE)
	}
	
	char buff[100];
        while (fgets( buff, 100, fptr )){
            printf("The line is: %s\n", buff);
        }
        
        
        // create array of strings
        
	fclose(fptr);

}
