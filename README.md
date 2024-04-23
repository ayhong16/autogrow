﻿# AutoGrow Device

## Development Instructions

1. Add both of these links to additional board urls:
   1. <https://ropg.github.io/heltec_boards/boards.json>
   2. <https://espressif.github.io/arduino-esp32/package_esp32_index.json>
2. Open *Arduio board manager*
3. Refresh package indexes
4. Search for and install **Heltec (unofficial)**
5. Open *Arduino library manager*
6. Install the following packages
   1. **Heltec_ESP32_LoRa_v3**
   2. **DHT sensor library**
   3. **DFRobot_ESP_PH_WITH_ADC_BY_GREENPONIK**
7. Set board type to **ESP32 LoRa v3 (Heltec (unofficial))**
8. Copy `main/src/secrets.h.example` to `secrets.h` and fill out information
