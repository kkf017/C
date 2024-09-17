#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define FILE1 "./TestFiles/corn.txt"//"./34-haiku.pdf"
#define FILE2 "./KITTYhaikussss.txt"
#define FSIZE 6
#define STRSIZE 64

		      // WARNING !! Last character of file (.c, .sh...) missing.
		      //		not working with img.



	// tester avec differents types de fichiers
	//	read .pdf, .doc ..., img ...
	// send random data (bytes) - FileInputStream() (r/w bytes)
	// msg


int main(int argc, char *argv[]){
	
	FILE* file1 = fopen(FILE1, "r");
	if (file1 == NULL){
	     perror("\n\033[0;91m[-]ERROR: Could not open input file.\033[0m");
	     exit(0);
	}
	
	FILE* file2 = fopen(FILE2, "w");
	if (file2 == NULL){
	     perror("\n\033[0;91m[-]ERROR: Could not open outsput file.\033[0m");
	     exit(0);
	}
	    
	    
	int i,j;
	int flag = 1;
	int x;
	int bytes[FSIZE+2];
	while(flag){

        	for(i=0;i<FSIZE;i++){
        		x = fread(&bytes[i], sizeof(int), 1, file1); //  reading a single byte into an int
        		if(x != 1){
        			//flag = 0;
        			bytes[FSIZE+1] = 1;
        			break;
            		}
        	}
        	
        	bytes[FSIZE] = i; 
      
 
 
 
		
		for(i=0;i<bytes[FSIZE];i++){
            		if(bytes[FSIZE+1]){
        			flag = 0;
        			//break;
            		}
		      fwrite(&bytes[i], sizeof(int), 1, file2);	
	        }
	        
	        bzero(bytes, FSIZE+2);
    	}
    
    	fclose(file1);
    	fclose(file2);
    	printf("\n");
    
	return 1;
}
