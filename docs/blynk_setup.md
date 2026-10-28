# Blynk IoT Mobile App Setup Guide

### 1. Template Configuration
- **Hardware:** ESP32
- **Connection Type:** Wi-Fi

### 2. Datastream Definitions
| Virtual Pin | Name | Data Type | Min | Max | Unit |
|---|---|---|---|---|---|
| **V0** | Water Percentage | Integer | 0 | 100 | % |
| **V1** | Water Volume | Double | 0 | 1000 | Liters |
| **V2** | Raw Distance | Double | 0 | 400 | cm |
| **V3** | Pump Status | Integer (LED) | 0 | 1 | - |
| **V4** | Manual Switch | Integer (Button) | 0 | 1 | - |

### 3. Mobile Dashboard Widgets
- **Gauge Widget:** Attached to `V0` (Shows 0–100% water level).
- **Value Display:** Attached to `V1` (Shows remaining volume in Liters).
- **LED Indicator:** Attached to `V3` (Lights up green when pump is energized).
- **Button Widget:** Attached to `V4` (Push-to-toggle manual motor override).
