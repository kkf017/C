#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "./client.h"
#include "../Example/example.h"


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
    
    
    send_(sock, "Hello, from client.");
    char* response = rcv_(sock);
    printf("\n\033[0;35m\tFrom server:\033[0m %s", response);
    send_(sock, "Goodbye, from client.");
    

   /**********************/
 
    close(sock);
    printf("\n\033[0;92m[+]DONE: Disconnected from the server.\n\033[0m");
}


