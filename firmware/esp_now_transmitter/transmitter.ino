/*
 * Project: Wireless Water Tank Level Controller (Transmitter Node)
 * Author: Engr. Hanif Ullah (Engr. Hanif Khan)
 *
 * Protocol: ESP-NOW (2.4 GHz Peer-to-Peer, No Router Required)
 * Board: ESP32 / ESP32-C3
 */

#include <WiFi.h>
#include <esp_now.h>
#include "mac_config.h"

static const int PIN_LEVEL = 3; // Float switch / level trigger (LOW = Full)
uint8_t g_seq = 0;

void printMyMac() {
  uint8_t mac[6];
  WiFi.macAddress(mac);
  Serial.print(F("Transmitter MAC Address: {"));
  for (int i = 0; i < 6; i++) {
    Serial.printf("0x%02X%s", mac[i], (i < 5) ? ", " : "");
  }
  Serial.println(F("}"));
}

bool sendCmd(uint8_t cmd) {
  PumpPacket pkt = {PKT_MAGIC, cmd, g_seq++};
  const uint8_t *dest = macIsBroadcast(RECEIVER_MAC) ? nullptr : RECEIVER_MAC;
  esp_err_t e = esp_now_send(dest, (uint8_t *)&pkt, sizeof(pkt));
  Serial.printf("[ESP-NOW] Sent %s -> %s\n", cmd ? "ON" : "OFF", e == ESP_OK ? "SUCCESS" : "FAIL");
  return e == ESP_OK;
}

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.printf("[CALLBACK] Delivery status: %s\n", status == ESP_NOW_SEND_SUCCESS ? "DELIVERED" : "FAILED");
}

void setup() {
  pinMode(PIN_LEVEL, INPUT_PULLUP);
  Serial.begin(115200);
  delay(400);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  printMyMac();

  if (esp_now_init() != ESP_OK) {
    Serial.println(F("[ERROR] ESP-NOW initialization failed"));
    return;
  }

  esp_now_register_send_cb(onDataSent);

  // Register peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, RECEIVER_MAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println(F("[ERROR] Failed to add receiver peer"));
  }
}

void loop() {
  // Check float switch / level sensor state
  bool tankFull = (digitalRead(PIN_LEVEL) == LOW);
  if (tankFull) {
    sendCmd(0); // Tank full, request pump OFF
  } else {
    sendCmd(1); // Tank low, request pump ON
  }
  delay(5000); // Transmit heartbeat every 5 seconds
}
