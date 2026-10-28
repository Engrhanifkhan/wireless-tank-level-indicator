/*
 * Project: Wireless Water Tank Level Controller (Receiver Node)
 * Author: Engr. Hanif Ullah (Engr. Hanif Khan)
 *
 * Board: ESP32 (Pump Side)
 * Actuator: Relay / Motor Contactor on PIN_RELAY
 */

#include <WiFi.h>
#include <esp_now.h>
#include "mac_config.h"

static const int PIN_RELAY = 4;
unsigned long lastPacketTime = 0;
const unsigned long WATCHDOG_TIMEOUT = 15000; // 15 sec failsafe

void setPump(bool state) {
  digitalWrite(PIN_RELAY, state ? HIGH : LOW);
  Serial.printf("[RECEIVER] Pump relay switched: %s\n", state ? "ON" : "OFF");
}

void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  if (len != sizeof(PumpPacket)) return;

  PumpPacket pkt;
  memcpy(&pkt, data, sizeof(PumpPacket));

  if (pkt.magic != PKT_MAGIC) return; // Discard invalid packet

  lastPacketTime = millis();
  Serial.printf("[RECEIVER] Valid packet received (cmd: %d, seq: %d)\n", pkt.cmd, pkt.seq);
  setPump(pkt.cmd == 1);
}

void setup() {
  pinMode(PIN_RELAY, OUTPUT);
  setPump(false); // Default to SAFE OFF

  Serial.begin(115200);
  delay(400);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println(F("[ERROR] ESP-NOW init failed on receiver"));
    return;
  }

  esp_now_register_recv_cb(onDataRecv);
  Serial.println(F("[RECEIVER] Listening for tank transmitter packets..."));
}

void loop() {
  // Failsafe Watchdog: If no packet received within timeout, turn OFF pump
  if (millis() - lastPacketTime > WATCHDOG_TIMEOUT) {
    static bool watchdogTriggered = false;
    if (!watchdogTriggered) {
      Serial.println(F("[WATCHDOG] Communication timeout! Shutting down pump for safety."));
      setPump(false);
      watchdogTriggered = true;
    }
  }
}
