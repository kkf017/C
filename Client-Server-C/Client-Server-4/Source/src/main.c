/******************************************************************
Client/Server model (with encryption).

	Server:
		./exec -o -p [port]
	Client:
		./exec -h [ip_address] -p [port] -rsa
		
*******************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include "./Client/Client.h"
#include "./Server/Server.h"


#define BUFFER 250


int parse(int argc, char *argv[]){

	char host[16] = "000.000.000.000";
	int port = 8080;
	int flag = 0, key = 1;
	char encrypt[BUFFER] = "-rsa";
	
	for(int i=1; i<argc ; i++){
	
		if(strcmp(*(argv+i), "-h") == 0){
			strcpy(host, *(argv+i+1));
		}
		
		if(strcmp(*(argv+i), "-p") == 0){
			port = atoi(*(argv+i+1));
		}
		
		if(strcmp(*(argv+i), "-o") == 0){
			flag = 1;
		}
		
		
		/*if(strcmp(*(argv+i), "-rsa") == 0 || strcmp(*(argv+i), "-elgamal") == 0 ||strcmp(*(argv+i), "-rabin") == 0){
			strcpy(encrypt, *(argv+i));
		}*/	
		
	}
	
	if(!flag && strcmp(host, "000.000.000.000") == 0){
		perror("\n\033[0;91m[-]ERROR: Unknown host (-h).\033[0m");
        	exit(EXIT_FAILURE);
	}
	
	char command[BUFFER] = "python3 ../library/main.py";
	if(key){ 
		strcpy(command,"python3 ../library/main.py -key ");
		strcat(command, encrypt);
   		system(command);
   		//return 1;
	}
		
	
	if(flag){
		server(port, encrypt);
				
	}else{
		client(host, port, encrypt);
	}
	
	system("python3 ../library/main.py -erase");
   	
	return 1;
}

int main(int argc, char *argv[]){
	parse(argc, argv);
	return 0;
}
