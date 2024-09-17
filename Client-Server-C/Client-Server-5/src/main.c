/******************************************************************
Client/Server model (to exchange messages).

	Server:
		./exec -o -p [port]
	Client:
		./exec -h [ip_address] -p [port]
		
*******************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./Client/client.h"
#include "./Server/server.h"


int command(int argc, char *argv[]){

	char host[16] = "000.000.000.000";
	int port = 8080;
	int flag = 0;
	char type[8] = "-rsa";
	
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
	}
	
	if(!flag && strcmp(host, "000.000.000.000") == 0){
		perror("\n\033[0;91m[-]ERROR: Unknown host (opt. -h).\033[0m");
        	exit(EXIT_FAILURE);
	}
	
	char command[64] = "python3 ./library/main.py";
	strcpy(command,"python3 ./library/main.py -key ");
	strcat(command, type);
   	system(command);	
	
	if(flag){
		server(port, type);
				
	}else{
		client(host, port, type);
	}
	
	system("python3 ./library/main.py -erase");
   	
	return 1;
}

int main(int argc, char *argv[]){
	command(argc, argv);
	return 0;
}
