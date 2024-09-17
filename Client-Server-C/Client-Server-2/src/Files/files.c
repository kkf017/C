#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "files.h"

#define FSIZE 10
#define STRSIZE 64

char* file(char* filename){
	char* str = malloc((1+strlen(filename))*sizeof(char));
	for(int i = 0; i < strlen(filename); i++){
		*(str+i) = *(filename+i);
	}
	char* f;
	char delim[] = "/";
	char* ptr = strtok(str, delim);

	while(ptr != NULL)
	{
		//printf("'%s'\n", ptr);
		f = ptr;
		ptr = strtok(NULL, delim);
	}
	return f;
}

void send_(int sock, char* filename){
    char* f = file(filename);
    char* folder = malloc((16+strlen(f))*sizeof(char));
    strcat(folder, "./data/");
    strcat(folder, f);
 
    char buff[STRSIZE];
    bzero(buff, STRSIZE);
    strcpy(buff, folder);
    send(sock, buff, strlen(buff), 0);
    bzero(buff, STRSIZE);

    FILE* file = fopen(filename, "r");
    if (file == NULL){
     perror("\n\033[0;91m[-]ERROR: Could not open input file.\033[0m");
     exit(0);
    }

    int i;
    char x;
    char buffer[FSIZE];
    while(x != EOF){

        for(i=0;i<FSIZE;i++){
            x = fgetc(file);
            buffer[i] = x;            
            if(x == EOF){
                break;
            }
            //printf("%c",buffer[i]); // vers. with ./server > myprog.py
        }
        send(sock, buffer, strlen(buffer), 0);
        bzero(buffer, FSIZE);
    }
    
    fclose(file);
}


void rcv_(int sock){
    	char buff[STRSIZE];  
	bzero(buff, STRSIZE);
    	recv(sock, buff, sizeof(buff), 0);
    	
    	char filename[STRSIZE];
    	strcpy(filename, buff);
    	bzero(buff, STRSIZE);
    	
	FILE* file = fopen(filename, "w");
	printf("\n\nRcv file: %s", filename);
	if (file == NULL){
	     perror("\n\033[0;91m[-]ERROR: Could not open output file.\033[0m");
	     exit(0);
	}
	
	int i;
	int flag=1;
	char buffer[FSIZE];
	while(flag){
	
		bzero(buffer, FSIZE);
		recv(sock, buffer, sizeof(buffer), 0);
		
		for(i=0;i<FSIZE;i++){
            		if(buffer[i] == EOF){
            			flag=0;
                		break;
			}
		      fputc(buffer[i], file); // vers. with file creation
	              //printf("%c",buffer[i]); // vers. with ./server > myprog.py
	        }
	}
}
