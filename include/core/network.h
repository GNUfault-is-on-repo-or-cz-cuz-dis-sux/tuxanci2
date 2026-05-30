#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>

#define CONNECT_MAGIC 0x1
#define CONNECTED_MAGIC 0x2

struct ConnectPacket {
    uint32_t magic;
    uint32_t version;
};

struct ConnectedPacket {
    uint32_t magic;
    uint32_t client_id;
};

#endif // NETWORK_H
