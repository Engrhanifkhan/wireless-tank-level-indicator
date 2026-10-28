/*
 * Project: Wireless Water Tank Level Monitor & Automatic Pump Controller
 * Author: Engr. Hanif Ullah (Engr. Hanif Khan)
 * Institution: CISNR, UET Peshawar
 *
 * Board: ESP32 / ESP32-C3 Super Mini
 * Sensor: AJ-SR04M Waterproof Ultrasonic or HC-SR04
 * Actuator: Solid State Relay (SSR) / Mechanical Relay Module
 * Cloud: Blynk IoT
 */

#define BLYNK_TEMPLATE_ID   "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Water Tank Level"
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <Preferences.h>
#include <BlynkSimpleEsp32.h>
#include "config.h"

Preferences prefs;
BlynkTimer timer;

// State Variables
float waterLevelCm = 0.0;
float waterPercentage = 0.0;
float currentLiters = 0.0;
bool pumpRunning = false;
bool manualOverride = false;

// Safe Relay Control
void setPumpState(bool state) {
  pumpRunning = state;
  int writeVal = RELAY_ACTIVE_LOW ? (!state) : state;
  digitalWrite(RELAY_PIN, writeVal);
  Blynk.virtualWrite(V_PUMP_STATUS, pumpRunning ? 1 : 0);
  Serial.printf("[PUMP] State changed to: %s\n", state ? "ON" : "OFF");
}

// Measure distance using ultrasonic pulse
float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  if (duration == 0) {
    Serial.println(F("[WARN] Ultrasonic echo timeout / sensor out of range"));
    return -1.0;
  }

  // Speed of sound = 343 m/s = 0.0343 cm/us
  float distance = (duration * 0.0343f) / 2.0f;
  return distance;
}

// Periodic measurement task
void measureTankLevel() {
  float distance = readDistanceCm();
  if (distance < 0) return; // Ignore failed reads

  // Calculate actual water height from bottom of tank
  float level = EMPTY_DISTANCE_CM - distance;
  if (level < 0) level = 0;
  if (level > TANK_HEIGHT_CM) level = TANK_HEIGHT_CM;

  waterLevelCm = level;
  waterPercentage = (waterLevelCm / TANK_HEIGHT_CM) * 100.0f;
  currentLiters = (waterPercentage / 100.0f) * TANK_CAPACITY_LITERS;

  // Push to Blynk datastreams
  Blynk.virtualWrite(V_LEVEL_PERCENT, (int)waterPercentage);
  Blynk.virtualWrite(V_LEVEL_LITERS, currentLiters);
  Blynk.virtualWrite(V_RAW_DISTANCE, distance);

  Serial.printf("[TELEMETRY] Dist: %.1f cm | Level: %.1f cm | Water: %.1f%% (%.0f L)\n",
                distance, waterLevelCm, waterPercentage, currentLiters);

  // Automatic Pump Logic (if manual override is OFF)
  if (!manualOverride) {
    if (waterPercentage <= AUTO_START_PERCENT && !pumpRunning) {
      Serial.println(F("[AUTO] Water level low. Starting pump..."));
      setPumpState(true);
    } else if (waterPercentage >= AUTO_STOP_PERCENT && pumpRunning) {
      Serial.println(F("[AUTO] Water level full. Stopping pump..."));
      setPumpState(false);
    }
  }
}

// Blynk Remote Button Callback
BLYNK_WRITE(V_MANUAL_BUTTON) {
  int val = param.asInt();
  manualOverride = (val == 1);
  if (manualOverride) {
    setPumpState(true);
  } else {
    setPumpState(false);
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println(F("\n=== ESP32 Wireless Water Tank Controller ==="));

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Ensure pump defaults to SAFE OFF on power-up
  setPumpState(false);

  // Connect to Wi-Fi & Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  // Set periodic measurement interval (every 2 seconds)
  timer.setInterval(2000L, measureTankLevel);

  Serial.println(F("[INIT] Setup complete. System operational."));
}

void loop() {
  Blynk.run();
  timer.run();
}
