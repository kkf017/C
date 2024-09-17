#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "message.h"

#define BUFFER 64


void send_(int sock, char* msg){
    char buffer[BUFFER];
    bzero(buffer, BUFFER);
    strcpy(buffer, msg);
    send(sock, buffer, strlen(buffer), 0);

}


char* rcv_(int sock){
    static char buffer[BUFFER];
    bzero(buffer, BUFFER);
    recv(sock, buffer, sizeof(buffer), 0);
    return buffer; 
}


void msend(int sock){
    char buffer[BUFFER];

    bzero(buffer, BUFFER);
    recv(sock, buffer, sizeof(buffer), 0);
    //printf("\n\033[0;35m\tFrom server:\033[0m %s. \n", buffer);

    bzero(buffer, BUFFER);
    strcpy(buffer, "Hello, from client");
    send(sock, buffer, strlen(buffer), 0);
    
    printf("\n\n");
    
    /*------------------------------------
    	Complete with Messages.
    ------------------------------------*/
    bzero(buffer, BUFFER);
    printf("\033[0;35m\t@Client: \033[0m");
    fgets(buffer, BUFFER, stdin);
    send(sock, buffer, strlen(buffer), 0);
    
    bzero(buffer, BUFFER);
    recv(sock, buffer, sizeof(buffer), 0);
    printf("\033[0;35m\t@Server:\033[0m %s.", buffer);
    
    /*------------------------------------*/

    bzero(buffer, BUFFER);
    recv(sock, buffer, sizeof(buffer), 0);
    //printf("\n\n\033[0;35m\tFrom server:\033[0m %s.MSG", buffer);

}


void mrcv(int sock){
    char buffer[BUFFER];
    bzero(buffer, BUFFER);
    strcpy(buffer, "Hello, from server");
    send(sock, buffer, strlen(buffer), 0);
         
    bzero(buffer, BUFFER);
    //printf("\nWaiting...");
    recv(sock, buffer, sizeof(buffer), 0);
    //printf("\n\033[0;35m\tFrom client:\033[0m %s. \n", buffer); 

    
    printf("\n");
    /*------------------------------------
    	Complete with Messages.
    ------------------------------------*/
    bzero(buffer, BUFFER);
    recv(sock, buffer, sizeof(buffer), 0);
    printf("\033[0;35m\t@Client:\033[0m %s.", buffer); 
    
    bzero(buffer,  BUFFER);
    printf("\033[0;35m\t@Server: \033[0m");
    fgets(buffer,  BUFFER, stdin);
    send(sock, buffer, strlen(buffer), 0);
    
    /*------------------------------------*/
      
    bzero(buffer,  BUFFER);
    strcpy(buffer, " ");
    send(sock, buffer, strlen(buffer), 0);

}

