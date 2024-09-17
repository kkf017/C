#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


#include "Server.h"
#include "../Example/Example.h"

#define BUFF 250
#define TIMEWAIT 15



void server(int port, char* type){

    int PubKeyClient[3] = {0,0,0};
    int PubKeyServer[3] = {0,0,0};
    getPublicKey(PubKeyServer, type);
    printf("\n\nPublic key (server): %d %d %d", PubKeyServer[0], PubKeyServer[1], PubKeyServer[2]);
   

    int sockServer, sockClient;
    struct sockaddr_in addrServer, addrClient;
    socklen_t addrSize;
 

    sockServer = socket(AF_INET, SOCK_STREAM, 0);
    if (sockServer < 0){
        perror("\n\033[0;91m[-]ERROR: Socket not created.\033[0m");
        exit(EXIT_FAILURE);
    }


    memset(&addrServer, '\0', sizeof(addrServer));
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(port);
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY);


    if (bind(sockServer, (struct sockaddr*)&addrServer, sizeof(addrServer)) < 0){
        perror("\n\033[0;91m[-]ERROR: Bind error.\033[0m");
        exit(EXIT_FAILURE);
    }

    if(listen(sockServer, TIMEWAIT) < 0){
        perror("\n\033[0;91m[-]ERROR: Listen on server.\033[0m");
       	exit(EXIT_FAILURE);
    }
    //printf("\n\033[0;30mListening on port %d...\033[0m", port);


    //while(1){
        addrSize = sizeof(addrClient);
        sockClient = accept(sockServer, (struct sockaddr*)&addrClient, &addrSize);
        if(sockClient < 0){
            perror("\n\033[0;91m[-]ERROR: Bind error.\033[0m");
            exit(EXIT_FAILURE);
        }
        printf("\n\033[0;92m[+]DONE: Client connected.\033[0m");


        /*** CHANGE THIS PART ***/
        
	handshake(sockClient, -1);
    	handshake(sockClient, 1);
    	handshake(sockClient, -1);
    
	keyExchange(sockClient, PubKeyClient, -1);
	keyExchange(sockClient, PubKeyServer, 1);
	printf("\n\033[0;33m\tPublic Key (from Client):\033[0m %d %d %d.", *(PubKeyClient), *(PubKeyClient+1), *(PubKeyClient+2));
	
        
        char* msg = rcall(sockClient, type);
        printf("\n\033[0;35m\tFrom client:\033[0m %s", msg);
        
        
        handshake(sockClient, 1);
    	handshake(sockClient, -1);
    	handshake(sockClient, 1); 

        /**********************/
        
        close(sockClient);
    //}

    close(sockServer);
    printf("\n\033[0;92m[+]DONE: Disconnected from the client.\n\033[0m");

}






