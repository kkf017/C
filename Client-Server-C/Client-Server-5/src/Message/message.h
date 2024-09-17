#ifndef MSG
#define MSG

void __send__(int sock, char* msg);
char* __rcv__(int sock);

void _send_(int sock, char* msg, int key[], char* type);
char* _rcv_(int sock, char* type);

#endif
