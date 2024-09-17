#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


#include "./server.h"
#include "../Example/example.h"


#define TIMEWAIT 15


void server(int port){

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
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY); // addr.sin_addr.s_addr = inet_addr(ip);


    if (bind(sockServer, (struct sockaddr*)&addrServer, sizeof(addrServer)) < 0){
        perror("\n\033[0;91m[-]ERROR: Bind error.\033[0m");
        exit(EXIT_FAILURE);
    }

    if(listen(sockServer, TIMEWAIT) < 0){
        perror("\n\033[0;91m[-]ERROR: Listen on server.\033[0m");
       	exit(EXIT_FAILURE);
    }
    printf("\n\033[0;30mListening on port %d...\033[0m", port);


    //while(1){
        addrSize = sizeof(addrClient);
        sockClient = accept(sockServer, (struct sockaddr*)&addrClient, &addrSize);
        if(sockClient < 0){
            perror("\n\033[0;91m[-]ERROR: Bind error.\033[0m");
            exit(EXIT_FAILURE);
        }
        printf("\n\033[0;92m[+]DONE: Client connected.\033[0m");


        /*** CHANGE THIS PART ***/


        char* response = rcv_(sockClient);
        printf("\n\033[0;35m\tFrom client:\033[0m %s", response);
        send_(sockClient, "Hello, from Server.");
        response = rcv_(sockClient);
        printf("\n\033[0;35m\tFrom client:\033[0m %s", response);

        /**********************/
        
        close(sockClient);
    //}

    close(sockServer);
    printf("\n\033[0;92m[+]DONE: Disconnected from the client.\n\033[0m");

}


