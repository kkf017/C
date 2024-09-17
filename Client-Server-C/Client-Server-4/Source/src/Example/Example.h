#ifndef EXAMPLE
#define EXAMPLE 

void getPublicKey(int key[], char* encrypt);
void handshake(int sock, int type);
void keyExchange(int sock, int key[], int type);

void scall(int sock, char* msg, int key[], char* encrypt);
char* rcall(int sock, char* type);

#endif
