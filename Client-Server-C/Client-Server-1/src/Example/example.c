#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "example.h"

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
