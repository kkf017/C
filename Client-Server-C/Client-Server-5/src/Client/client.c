#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../global.h"
#include "./client.h"
#include "../Message/message.h"
#include "../Protocol/protocol.h"


void client(char* host, int port, char* type){
    
    int PubKeyClient[3] = {0,0,0};
    int PubKeyServer[3] = {0,0,0};
    getPublicKey(PubKeyClient, type);
    //printf("\n\nPublic key (client): %d %d %d", PubKeyClient[0], PubKeyClient[1], PubKeyClient[2]);
   

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
    inet_pton(AF_INET, (char*) host, &(addr.sin_addr) ); 


    if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        perror("\n\033[0;91m[-]ERROR: Socket not created.\033[0m");
        //exit(EXIT_FAILURE);
    }
    printf("\n\033[0;92m[+]DONE: Connected to the server.\033[0m");



    /*** CHANGE THIS PART ***/
    
    
    __send__(sock, "HELO");
    char* response = __rcv__(sock);
    __send__(sock, "HELO");
    
    keyExchange(sock, PubKeyClient, 1);
    keyExchange(sock, PubKeyServer, -1);
    //printf("\n\033[0;33m\tPublic Key (from Server):\033[0m %d %d %d.", *(PubKeyServer), *(PubKeyServer+1), *(PubKeyServer+2));
    
    
    int flag = 1;
    while(flag){
    
    	printf("\n\033[0;35m\t@Client: \033[0m\n");
    	while(1){
    		if(!flag){
    			break;
    		}
    		char buffer[BUFFER];
    		bzero(buffer, BUFFER);
    		printf("\t\033[0;35m      >>\033[0m");
		fgets(buffer, BUFFER, stdin);
		_send_(sock, buffer, PubKeyServer, type);
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
        	char* msg = _rcv_(sock, type);
        	if(strcmp(msg, "\n") == 0){
        		break;
        	}
        	if(strstr(msg, "quit") != NULL){
				flag = 0;
        			break;
        	}
        	printf("\t\033[0;33m      >>\033[0m%s", msg);
    	}
    	
    }
    

   /**********************/
 
    close(sock);
    printf("\n\033[0;92m[+]DONE: Disconnected from the server.\n\033[0m");
}


