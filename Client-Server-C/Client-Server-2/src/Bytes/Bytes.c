#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "Bytes.h"

#define BSIZE 10
#define BSTRSIZE 64

	// Warning !! not working.
	//	received file is damaged.
	

void bsend(int sock, char* filename){

    char buff[BSTRSIZE];
    bzero(buff, BSTRSIZE);
    strcpy(buff, "./haikussss.pdf"); //filename);
    send(sock, buff, strlen(buff), 0);
    bzero(buff, BSTRSIZE);

    /*------------------------------
    	COMPLETER ! (avec pdff.c)
    -------------------------------*/
   FILE* file = fopen(filename, "r");
   if (file == NULL){
   	perror("\n\033[0;91m[-]ERROR: Could not open input file.\033[0m");
	exit(0);
   }

   int i;
   int flag = 1;
   int x;
   int bytes[BSIZE+2];
   while(flag){
   
	for(i=0;i<BSIZE;i++){
		x = fread(&bytes[i], sizeof(int), 1, file); // reading a single byte into an int
		if(x != 1){
			flag = 0;
			bytes[BSIZE+1] = 1;
			break;
		}
        }
        bytes[BSIZE] = i;
        
        send(sock, bytes, (BSIZE+2)*sizeof(int), 0);
        bzero(bytes, BSIZE+2);
   }
   fclose(file);
}


void brcv(int sock){
    	char buff[BSTRSIZE];  
	bzero(buff, BSTRSIZE);
    	recv(sock, buff, sizeof(buff), 0);
    	
    	char filename[BSTRSIZE];
    	strcpy(filename, buff);
    	bzero(buff, BSTRSIZE);
    	
    	printf("\n\033[0;35m\tFilename received from client:\033[0m %s.", filename);
    	
	/*---------------------------------
    	  	COMPLETER ! (avec pdff.c)
    	-----------------------------------*/
    	FILE* file = fopen(filename, "w");
	if (file == NULL){
	     perror("\n\033[0;91m[-]ERROR: Could not open output file.\033[0m");
	     exit(0);
	}
	
	int i;
	int flag = 1;
	int bytes[BSIZE+2];
	while(flag){
		
		bzero(bytes, BSIZE+2);
		recv(sock, bytes, (BSIZE+2)*sizeof(int), 0);
		
		for(i=0;i<bytes[BSIZE];i++){
            		if(bytes[BSIZE+1]){
        			flag = 0;
        			//break;
            		}
		      fwrite(&bytes[i], sizeof(int), 1, file);	
	        }
	}
	fclose(file);
}
