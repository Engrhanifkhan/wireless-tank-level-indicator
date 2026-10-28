/*
 * Project: ESP-NOW Peer Configuration & Packet Definition
 */

#ifndef MAC_CONFIG_H
#define MAC_CONFIG_H

#include <stdint.h>

#define PKT_MAGIC 0x57 // 'W' for Water

struct __attribute__((packed)) PumpPacket {
  uint8_t magic;
  uint8_t cmd;  // 0 = OFF, 1 = ON
  uint8_t seq;
};

// Replace with your Receiver's actual MAC address
static const uint8_t RECEIVER_MAC[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

static inline bool macIsBroadcast(const uint8_t *mac) {
  for (int i = 0; i < 6; i++) {
    if (mac[i] != 0xFF) return false;
  }
  return true;
}

#endif // MAC_CONFIG_H
