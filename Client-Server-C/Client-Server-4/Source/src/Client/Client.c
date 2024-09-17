#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "Client.h"
#include "../Example/Example.h"


#define BUFF 250


void client(char* host, int port, char* type){

    int PubKeyClient[3] = {0,0,0};
    int PubKeyServer[3] = {0,0,0};
    getPublicKey(PubKeyClient, type);
    printf("\n\nPublic key (client): %d %d %d", PubKeyClient[0], PubKeyClient[1], PubKeyClient[2]);
   
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
    
    handshake(sock, 1);
    handshake(sock,-1);
    handshake(sock, 1);
    
    
    keyExchange(sock, PubKeyClient, 1);
    keyExchange(sock, PubKeyServer, -1);
    printf("\n\033[0;33m\tPublic Key (from Server):\033[0m %d %d %d.", *(PubKeyServer), *(PubKeyServer+1), *(PubKeyServer+2));
    
  
    //char msg[128] = "@@@Hello :) smiLilly loves U. $$$ MagicUnixcorn";  
    char msg[128] = "@@@Hello :) smiLilly loves U. <3";
    scall(sock, msg, PubKeyServer, type);
    
    
    handshake(sock, -1);
    handshake(sock, 1);
    handshake(sock, -1);  

   /**********************/
 
    close(sock);
    printf("\n\033[0;92m[+]DONE: Disconnected from the server.\n\033[0m");
}








