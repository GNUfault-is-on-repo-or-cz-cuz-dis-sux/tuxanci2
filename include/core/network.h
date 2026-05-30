#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>

#define CONNECT_MAGIC   0x1
#define CONNECTED_MAGIC 0x2
#define MOVE_MAGIC      0x3
#define MOVE_ACK_MAGIC  0x4

struct ConnectPacket {
    uint32_t magic;
    uint32_t version;
};

struct ConnectedPacket {
    uint32_t magic;
    uint32_t client_id;
};

struct MovePacket {
    uint32_t magic;
    uint32_t client_id;
    float    x, y, z;
};

struct MoveAckPacket {
    uint32_t magic;
    uint32_t client_id;
    float    x, y, z;
    uint32_t sequence;
};

#endif // NETWORK_H
