/*
 * Project: Wireless Water Tank Level Indicator
 * Configuration Parameters & Geometry Calibration
 */

#ifndef CONFIG_H
#define CONFIG_H

// --- Wi-Fi Credentials ---
#define WIFI_SSID           "YOUR_WIFI_SSID"
#define WIFI_PASS           "YOUR_WIFI_PASSWORD"

// --- Hardware Pin Definitions ---
#define TRIG_PIN            5
#define ECHO_PIN            18
#define RELAY_PIN           4
#define RELAY_ACTIVE_LOW    1

// --- Tank Geometry Calibration (cm) ---
#define TANK_HEIGHT_CM        100.0f
#define SENSOR_OFFSET_CM      5.0f
#define TANK_CAPACITY_LITERS  500.0f
#define EMPTY_DISTANCE_CM     (TANK_HEIGHT_CM + SENSOR_OFFSET_CM)

// --- Automatic Thresholds (%) ---
#define AUTO_START_PERCENT    20.0f  // Turn ON pump when level falls below 20%
#define AUTO_STOP_PERCENT     95.0f  // Turn OFF pump when level reaches 95%

// --- Blynk Virtual Pin Mappings ---
#define V_LEVEL_PERCENT       V0
#define V_LEVEL_LITERS        V1
#define V_RAW_DISTANCE        V2
#define V_PUMP_STATUS         V3
#define V_MANUAL_BUTTON       V4

#endif // CONFIG_H
