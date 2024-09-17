#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "./client.h"
#include "../Message/message.h"


#define BUFFER 1024

void client(char* host, int port){

    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        perror("\n\033[0;91m[-]ERROR: Socket not created.\033[0m");
        exit(EXIT_FAILURE);
    }

 
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, (char*) host, &(addr.sin_addr) ); //addr.sin_addr.s_addr = inet_addr(ip);


    if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        perror("\n\033[0;91m[-]ERROR: Socket not created.\033[0m");
        //exit(EXIT_FAILURE);
    }
    printf("\n\033[0;92m[+]DONE: Connected to the server.\033[0m");



    /*** CHANGE THIS PART ***/
    
    
    send_(sock, "HELO");
    char* response = rcv_(sock);
    send_(sock, "HELO");
    
    // start exchange
    int flag = 1;
    while(flag){
    
    	printf("\n\033[0;35m\t@Client: \033[0m\n");
    	while(1){
    		if(!flag){
    			break;
    		}
    		char buffer[BUFFER];
    		bzero(buffer, BUFFER);
    		printf("\t\033[0;35m      \033[0m");
		fgets(buffer, BUFFER, stdin);
		send_(sock, buffer);
		if(strcmp(buffer, "\n") == 0){
			break;
		}
		if(strstr(buffer, "quit") != NULL){
			flag = 0;
        		break;
        	}
    	}
    	
    	printf("\n\033[0;33m\t@Server: \033[0m\n");
    	while(1){
    		if(!flag){
    			break;
    		}
        	char* msg = rcv_(sock);
        	if(strcmp(msg, "\n") == 0){
        		break;
        	}
        	if(strstr(msg, "quit") != NULL){
				flag = 0;
        			break;
        	}
        	printf("\t\033[0;35m      \033[0m%s", msg);
    	}
    	
    }
    

   /**********************/
 
    close(sock);
    printf("\n\033[0;92m[+]DONE: Disconnected from the server.\n\033[0m");
}


