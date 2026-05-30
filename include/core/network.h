/*
 * Tuxánci 2 - Successor to Tuxánci
 * Copyright (C) 2026  Connor Thomson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file network.h
 * @brief tuxanci2 game server details
 */

#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>

#define MAX_CLIENTS 8

#define CONNECT_MAGIC      0x1
#define CONNECTED_MAGIC    0x2
#define MOVE_MAGIC         0x3
#define MOVE_ACK_MAGIC     0x4
#define PLAYER_STATE_MAGIC 0x5

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
    float x, y, z;
    float yaw, pitch;
};

struct MoveAckPacket {
    uint32_t magic;
    uint32_t client_id;
    float x, y, z;
    float yaw, pitch;
    uint32_t sequence;
};

struct PlayerStatePacket {
    uint32_t magic;
    uint32_t client_id;
    float x, y, z;
    float yaw, pitch;
};

#endif // NETWORK_H
