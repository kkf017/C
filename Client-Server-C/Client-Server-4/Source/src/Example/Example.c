#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "Example.h"

#define COMMAND 250
#define BUFFER 16  // handshake(), scall
#define ENCRYPT 1024 // encrypt(), decrypt(), send_, rcv_() - largest unicode ~ 4bytes ~ 4*8*BUFFER


void getPublicKey(int key[], char* type){
	char command[COMMAND] = "python3 ../library/main.py -pub ";
	strcat(command, type);
   	system(command);
   	
        FILE *file = fopen("../data/temp", "r");
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
   	remove("../data/temp");
}


void handshake(int sock, int type){	

	char buffer[BUFFER];
    
	if(type == 1){
		bzero(buffer, BUFFER);
    		strcpy(buffer, "HELO");
    		send(sock, buffer, strlen(buffer), 0);
	}else if(type == -1){
		bzero(buffer, BUFFER );
    		recv(sock, buffer, sizeof(buffer), 0);
    		//printf("\n\033[0;33m\tFrom handshake:\033[0m %s.", buffer);
	}else{
		//perror("\n\033[0;91m[-]ERROR: Unknown type of encryption.\033[0m");
        	exit(EXIT_FAILURE);
	}
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
	
	char command[COMMAND] = "python3 ../library/main.py -e ";
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
   
   	static char buff[ENCRYPT];
   	FILE *file = fopen("../data/temp-encrypt", "r");
   	fscanf(file, "%s", buff);   	
   	fclose(file);
   	remove("../data/temp-encrypt");
 
   	return buff;
}

char* decrypt(char* msg, char* type){
	char command[COMMAND] = "python3 ../library/main.py -d ";
	strcat(command, "'");
	strcat(command, msg);
	strcat(command, "' ");	
	strcat(command, type);	
   	system(command);
   
   	static char buff[ENCRYPT];
   	FILE *file = fopen("../data/temp-decrypt", "r"); 
   	fgets(buff, ENCRYPT, file);	
   	fclose(file);
   	remove("../data/temp-decrypt");
   	
   	return buff;
}

void send_(int sock, char* msg){
    char buffer[ENCRYPT];
    bzero(buffer, BUFFER);
    strcpy(buffer, msg);
    send(sock, buffer, strlen(buffer), 0);
}

char* rcv_(int sock){
    static char buffer[ENCRYPT];
    bzero(buffer, BUFFER);
    recv(sock, buffer, sizeof(buffer), 0);
    return buffer;
}

void scall(int sock, char* msg, int key[], char* type){
	char buffer[BUFFER];
	
	char* encryption;
	
	int bytes = strlen(msg);
	int n = strlen(msg)/BUFFER;
	int r = strlen(msg) - n * BUFFER;
	
	send(sock, &bytes, sizeof(int), 0);
	
	int i,j;
	for(i = 0; i < n; i++){
		bzero(buffer, BUFFER);
		for(j = 0; j < BUFFER ; j++){
			buffer[j] = *(msg+ i*BUFFER + j);
		}
		encryption = encrypt(buffer, key, type);
		//printf("\n\n%d, %d->%d", i, i*BUFFER, (i+1)*BUFFER); 
		//printf("\n%s (%ld)",encryption, strlen(encryption));
		
		send_(sock, encryption);
	}
	
	if(r != 0){
		char buff[r+1];
		bzero(buff, r+1);
		for(j = 0; j < r ; j++){
			buff[j] = *(msg+ i*BUFFER + j);
		}
		buff[r]='\0';
		encryption = encrypt(buff, key, type);
		//printf("\n\n%d, %d->%d", i, i*BUFFER, (i+1)*BUFFER); 
		//printf("\n%s (%ld)",encryption, strlen(encryption));
		
		send_(sock, encryption);
	}
}

char* rcall(int sock, char* type){
	int bytes;
	char* buffer;
	
	recv(sock, &bytes, sizeof(int), 0);
	
	int n = bytes/BUFFER;
	int r = bytes - n * BUFFER;
	
	
	char* msg = malloc((bytes+1)*sizeof(char));
	int count = 0;
	for(int i=0; i < n; i++){
		buffer = rcv_(sock);	
		buffer = decrypt(buffer, type);
		
		//printf("\n\tRcv message (rcall): %s, %ld", buffer, strlen(buffer));
		
		for(int j = 0; j < strlen(buffer); j++){
			*(msg+count) = buffer[j];
			count += 1;
		}
	}
	
	if(r != 0){
		buffer = rcv_(sock);	
		buffer = decrypt(buffer, type);
		
		//printf("\n\tRcv message (rcall): %s, %ld", buffer, strlen(buffer));
		
		for(int j = 0; j < r; j++){
			*(msg+count) = buffer[j];
			count += 1;
		}
	}
	
	*(msg+count) = '\0';
	return msg;
}





