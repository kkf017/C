#ifndef MSG
#define MSG


void send_(int sock, char* msg);
char* rcv_(int sock);

void msend(int sock);
void mrcv(int sock);

#endif
