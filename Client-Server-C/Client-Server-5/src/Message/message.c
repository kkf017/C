#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../global.h"
#include "message.h"
#include "../Protocol/protocol.h"



void __send__(int sock, char* msg){
    char buffer[BUFFER*4*8];
    bzero(buffer, BUFFER*4*8);
    strcpy(buffer, msg);
    send(sock, buffer, strlen(buffer), 0);

}


char* __rcv__(int sock){
    static char buffer[BUFFER*4*8];
    bzero(buffer, BUFFER*4*8);
    recv(sock, buffer, sizeof(buffer), 0);
    return buffer; 
}


void _send_(int sock, char* msg, int key[], char* type){
	char* cipher = encrypt(msg, key, type);
	__send__(sock, cipher);
}


char* _rcv_(int sock, char* type){
	char* cipher = __rcv__(sock);
	char* msg = decrypt(cipher, type);
	return msg;
}
