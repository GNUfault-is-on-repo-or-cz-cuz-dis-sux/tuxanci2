#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "core/network.h"

static int g_serverSock = -1;
static uint32_t g_nextClientId = 1;

void serverInit(int port) {
    g_serverSock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(g_serverSock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind failed");
        return;
    }
}

void serverUpdate(void) {
    uint8_t buffer[1024];

    struct sockaddr_in client;
    socklen_t len = sizeof(client);

    int n = recvfrom(g_serverSock, buffer, sizeof(buffer), MSG_DONTWAIT, (struct sockaddr*)&client, &len);

    if (n <= 0)
        return;

    if (n == sizeof(struct ConnectPacket)) {
        struct ConnectPacket *pkt = (struct ConnectPacket*)buffer;

        if (pkt->magic == CONNECT_MAGIC) {
            struct ConnectedPacket w = {
                .magic = CONNECTED_MAGIC,
                .client_id = g_nextClientId++
            };

            sendto(g_serverSock, &w, sizeof(w), 0, (struct sockaddr*)&client, len);
            return;
        }
    }

    if (n == sizeof(struct MovePacket)) {
        struct MovePacket *pkt = (struct MovePacket*)buffer;

        if (pkt->magic == MOVE_MAGIC) {
            struct MoveAckPacket ack = {
                .magic = MOVE_ACK_MAGIC,
                .client_id = pkt->client_id,
                .x = pkt->x,
                .y = pkt->y,
                .z = pkt->z,
                .sequence = 0
            };

            sendto(g_serverSock, &ack, sizeof(ack), 0, (struct sockaddr*)&client, len);
            return;
        }
    }
}

void serverDestroy(void) {
    if (g_serverSock >= 0) {
        close(g_serverSock);
        g_serverSock = -1;
    }
}
