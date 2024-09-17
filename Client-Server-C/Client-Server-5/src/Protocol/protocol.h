#ifndef PROTOCOL
#define PROTOCOL

void getPublicKey(int key[], char* type);
void keyExchange(int sock, int key[], int type);
char* encrypt(char* msg, int key[], char* type);
char* decrypt(char* msg, char* type);

#endif
