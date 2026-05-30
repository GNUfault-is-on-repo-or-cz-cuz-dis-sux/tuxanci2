#ifndef CLIENT_H
#define CLIENT_H

void clientInit(void);
void clientConnect(const char *ip, int port);
void clientDisconnect(void);
void clientDestroy(void);

#endif // CLIENT_H
