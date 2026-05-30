#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "core/network.h"

static int g_clientSock = -1;
static struct sockaddr_in g_serverAddr;
static uint32_t g_clientId = 0;

void clientInit(void) {
    g_clientSock = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&g_serverAddr, 0, sizeof(g_serverAddr));
}

void clientConnect(const char *ip, int port) {
    g_serverAddr.sin_family = AF_INET;
    g_serverAddr.sin_port = htons(port);
    inet_aton(ip, &g_serverAddr.sin_addr);

    struct ConnectPacket c = {
        .magic = CONNECT_MAGIC,
        .version = 1
    };

    sendto(g_clientSock, &c, sizeof(c), 0,
           (struct sockaddr*)&g_serverAddr, sizeof(g_serverAddr));

    uint8_t buffer[1024];
    socklen_t len = sizeof(g_serverAddr);

    int n = recvfrom(g_clientSock, buffer, sizeof(buffer), 0,
                     (struct sockaddr*)&g_serverAddr, &len);

    if (n == sizeof(struct ConnectedPacket)) {
        struct ConnectedPacket *w = (struct ConnectedPacket*)buffer;
        if (w->magic == CONNECTED_MAGIC) {
            g_clientId = w->client_id;
        }
    }
}

void clientDisconnect(void) {
    g_clientId = 0;
    memset(&g_serverAddr, 0, sizeof(g_serverAddr));
}

void clientDestroy(void) {
    clientDisconnect();
    if (g_clientSock >= 0) {
        close(g_clientSock);
        g_clientSock = -1;
    }
}
