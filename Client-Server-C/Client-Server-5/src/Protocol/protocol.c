#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../global.h"
#include "protocol.h"


void getPublicKey(int key[], char* type){
	char command[64] = "python3 ./library/main.py -pub ";
	strcat(command, type);
   	system(command);
   	
        FILE *file = fopen("./data/temp", "r");
   	if(strcmp(type, "-rsa") == 0){

   		fscanf(file, "%d %d", (key), (key+1));
   		
   	}else if(strcmp(type, "-elgamal") == 0){
   	
   		fscanf(file, "%d %d %d", (key), (key+1), (key+2));
   		
   	}else if(strcmp(type, "-rabin") == 0){
   	
   		fscanf(file, "%d", (key));
   		
   	}else{
   		perror("\n\033[0;91m[-]ERROR: Unknown type of encryption.\033[0m");
        	exit(EXIT_FAILURE);
   	}
   	
   	fclose(file);
   	
   	remove("./data/temp");
}

void keyExchange(int sock, int key[], int type){	
	if(type == 1){
		send(sock, (key), sizeof(*(key)), 0);
		send(sock, (key+1), sizeof(*(key+1)), 0);
		send(sock, (key+2), sizeof(*(key+2)), 0);
	}else if(type == -1){
		recv(sock, (key), sizeof(*(key)), 0);
		recv(sock, (key+1), sizeof(*(key+1)), 0);
		recv(sock, (key+2), sizeof(*(key+2)), 0);
	}else{
		//perror("\n\033[0;91m[-]ERROR: Unknown type of encryption.\033[0m");
        	exit(EXIT_FAILURE);
	}
}

char* encrypt(char* msg, int key[], char* type){
	int size = strlen(msg)+64;
	char buffer[size];
	
	char command[BUFFER+64] = "python3 ./library/main.py -e ";
	strcat(command, "'");
	strcat(command, msg);
	strcat(command, "' -k ");

	
	for(int i = 0; i < 3; i++){
		bzero(buffer, size);
		sprintf(buffer, "%d ", *(key+i));
		strcat(command, buffer);
		strcat(command, " ");
	}
	
	strcat(command, type);	
   	system(command);
   
   	static char buff[BUFFER*4*8];
   	FILE *file = fopen("./data/temp-encrypt", "r");
   	fscanf(file, "%s", buff);   	
   	fclose(file);
   	remove("../data/temp-encrypt");
 
   	return buff;
}

char* decrypt(char* msg, char* type){
	char command[BUFFER+64] = "python3 ./library/main.py -d ";
	strcat(command, "'");
	strcat(command, msg);
	strcat(command, "' ");	
	strcat(command, type);	
   	system(command);
   
   	static char buff[BUFFER*4*8];
   	FILE *file = fopen("./data/temp-decrypt", "r"); 
   	fgets(buff, BUFFER*4*8, file);	
   	fclose(file);
   	remove("../data/temp-decrypt");
   	
   	return buff;
}
