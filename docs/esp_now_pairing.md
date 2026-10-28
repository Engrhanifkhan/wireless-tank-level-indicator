# ESP-NOW Dual-Node Pairing Procedure

1. Upload the Transmitter sketch to the tank node and open Serial Monitor at 115200 baud.
2. Note the printed MAC address of the transmitter.
3. Upload the Receiver sketch to the pump node and note its MAC address.
4. Open `firmware/esp_now_transmitter/mac_config.h` and replace `RECEIVER_MAC` with the pump node's actual MAC address.
5. Re-flash the transmitter node.
6. The nodes will automatically establish instant peer-to-peer communication without any Wi-Fi router.
