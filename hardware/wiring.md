# Hardware Wiring Guide: Tank Level Indicator & Pump Control

## Voltage Divider Circuit for Ultrasonic Echo Pin
The ultrasonic Echo line outputs 5V. To safely interface with the 3.3V ESP32 GPIO, construct a voltage divider:

```text
                 +5V Supply
                     |
            +--------+--------+
            | AJ-SR04M / HC-SR04
            |                 |
ESP32 GPIO 5| TRIG            |
            |                 |
            |            ECHO +-----+
            +--------+--------+     |
                     |             [1k Resistor]
                    GND             |
                                    +--------> ESP32 GPIO 18 (Echo In, ~3.3V)
                                    |
                                   [2k Resistor]
                                    |
                                   GND
```

## Relay / SSR Connection

| Relay Terminal | Connection |
|---|---|
| **VCC** | 5V Power Supply |
| **GND** | System Ground |
| **IN** | ESP32 GPIO 4 |
| **COM** | AC Live / Motor Power Supply |
| **NO** (Normally Open) | Water Pump Motor Live Input |
