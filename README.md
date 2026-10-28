# Wireless Water Tank Level Indicator & Automatic Pump Controller

![MCU](https://img.shields.io/badge/MCU-ESP32--C3_Super_Mini_%2F_ESP32-red?style=for-the-badge&logo=espressif&logoColor=white)
![Sensor](https://img.shields.io/badge/Sensor-AJ--SR04M_%2F_HC--SR04-blue?style=for-the-badge)
![Protocol](https://img.shields.io/badge/Protocol-ESP--NOW_%2F_Blynk_IoT-brightgreen?style=for-the-badge)
![Relay](https://img.shields.io/badge/Actuator-SSR_%2F_Relay_Pump_Control-orange?style=for-the-badge)

An intelligent water resource automation platform designed to prevent dry-running, overflow, and manual pump switching. Features both **ESP-NOW ultra-low-latency peer-to-peer transmission** (connecting the overhead tank to the ground pump) and **Blynk IoT cloud monitoring**.

---

## 👨‍💻 Developer & Engineering Attribution

- **Engineer:** Engr. Hanif Ullah (Engr. Hanif Khan)
- **Specialization:** Hardware & Embedded Systems Engineer
- **Institution:** Centre of Intelligent Systems & Network Research (CISNR), UET Peshawar
- **WhatsApp / Phone:** [+92 315 9915537](https://wa.me/923159915537)
- **LinkedIn:** [Engr. Hanif Khan](https://www.linkedin.com/in/engr-hanif-khan-628a04259/)
- **Email:** [hanifullahshams@gmail.com](mailto:hanifullahshams@gmail.com)

---

## ⚡ Architecture & Dual Operating Modes

This repository provides two complete, tested architectures:

### Mode A: Cloud-Connected Unit (All-in-One / Wi-Fi)
Uses an **ESP32-C3 Super Mini** with an **AJ-SR04M waterproof ultrasonic sensor** located at the tank.
- Continuously calculates water level in centimeters, percentage, and remaining liters.
- Drives an onboard Solid State Relay (SSR) or mechanical relay module to cycle the pump.
- Transmits live metrics, overflow warnings, and dry-run alerts to the **Blynk IoT mobile app**.

### Mode B: Dual-Node ESP-NOW Peer-to-Peer Telemetry (No Internet Required)
Designed for sites where the overhead tank is distant from the pump motor and Wi-Fi is unavailable:
1. **Transmitter Node (Tank Side):** Reads liquid level / float sensors and transmits instant state packets over 2.4 GHz ESP-NOW directly to the pump receiver MAC address.
2. **Receiver Node (Pump Side):** Listens for heartbeat and state packets. Engages motor relay safely with automatic watchdog timeouts (shuts off motor if communication packet is lost).

---

## 📌 Hardware Pinout & Wiring

### Cloud Unit / Tank Node (ESP32-C3 Super Mini)

| Component | ESP32-C3 Pin | Mode | Description |
|---|---|---|---|
| **Ultrasonic TRIG** | GPIO 5 | Output | Trigger pulse (10 µs pulse) |
| **Ultrasonic ECHO** | GPIO 18 | Input | Echo return pulse (through 1kΩ/2kΩ divider) |
| **Pump Relay / SSR** | GPIO 4 | Output | Active LOW/HIGH pump control relay |
| **VCC** | 5V | Power | Sensor & relay power rail |
| **GND** | GND | Power | Common system ground |

> **⚠️ CRITICAL SAFETY NOTE:** Ultrasonic sensors (HC-SR04 / AJ-SR04M) operate on 5V and return a **5V Echo signal**. An ESP32 input pin is **not 5V tolerant**. Always use a resistor voltage divider ($1,	ext{k}Omega$ to Echo, $2,	ext{k}Omega$ to GND) on the Echo line to step down the signal to $3.3,	ext{V}$.

---

## 🧪 Testing Status & Authenticity Disclosure

- **✅ Firmware & Logic Verification:** The ESP-NOW packet protocol, sensor parsing, and motor relay state machines have been **bench-tested and verified**.
- **⚠️ Field Calibration (Testing Pending):** Tank geometry variables (`TANK_HEIGHT_CM`, `SENSOR_OFFSET_CM`, and `TANK_CAPACITY_LITERS`) must be calibrated for your specific reservoir volume before physical commissioning.
- **🔒 Security & Sanitization:** All sensitive credentials (Wi-Fi SSIDs, passwords, private MAC addresses, and Blynk Auth Tokens) have been removed from source code and replaced with clear configuration placeholders.

---

## 📁 Repository Structure

```text
wireless-tank-level-indicator/
├── README.md
├── LICENSE
├── .gitignore
├── firmware/
│   ├── water_tank_monitor/
│   │   ├── water_tank_monitor.ino       # All-in-one ultrasonic + SSR + Blynk firmware
│   │   └── config.h                     # Tank height, offset, and calibration parameters
│   ├── esp_now_transmitter/
│   │   ├── transmitter.ino              # ESP-NOW tank level transmitter node
│   │   └── mac_config.h                 # Peer MAC pairing configuration
│   └── esp_now_receiver/
│       ├── receiver.ino                 # ESP-NOW pump controller receiver node
│       └── mac_config.h                 # Receiver MAC configuration & watchdog
├── hardware/
│   ├── wiring.md                        # Voltage divider schematic & relay protection
│   └── components.md                    # Bill of materials
└── docs/
    ├── blynk_setup.md                   # Datastream mapping & virtual pin layout
    ├── esp_now_pairing.md               # MAC address pairing guide
    └── calibration.md                   # Offset measurement and volume calculation math
```

---

## 🚀 Setup & Deployment

### 1. Configuring Wi-Fi & Blynk
Open `firmware/water_tank_monitor/config.h` and enter your network credentials:
```cpp
#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Water Tank Level"
#define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN"

#define WIFI_SSID           "YOUR_WIFI_SSID"
#define WIFI_PASS           "YOUR_WIFI_PASSWORD"
```

### 2. Calibrating Reservoir Geometry
```cpp
#define TANK_HEIGHT_CM        100.0f  // Total height of the tank
#define SENSOR_OFFSET_CM      5.0f    // Distance from sensor face to max full level
#define TANK_CAPACITY_LITERS  500.0f  // Reservoir total capacity
```

---

## 📬 Contact & Commercial Inquiries

For industrial automation, custom PCB design, or firmware licensing:
- **Engr. Hanif Ullah** — [+92 315 9915537](https://wa.me/923159915537)
- **LinkedIn:** [linkedin.com/in/engr-hanif-khan-628a04259](https://www.linkedin.com/in/engr-hanif-khan-628a04259/)
- **Email:** [hanifullahshams@gmail.com](mailto:hanifullahshams@gmail.com)
