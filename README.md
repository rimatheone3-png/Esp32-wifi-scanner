Typhus Eye – ESP32 WiFi Network Scanner

A lightweight wireless network analysis tool built on an ESP32 microcontroller.
Typhus Eye scans all nearby WiFi networks, displays signal strength (dBm), encryption type and risk level and detects duplicate SSIDs with different MAC addresses, a common indicator of Evil Twin / rogue access point attacks.

What does it do : 
  Scans all visible WiFi networks in range
  Displays SSID, signal strength (dBm), encryption type and risk level for each network
  Shows the MAC address (BSSID) of each access point
  Detects rogue APs, flags duplicate SSIDs with different BSSIDs (Evil Twin detection)
  Outputs all results to the Serial Monitor in real time

Why this matters
  Duplicate SSIDs with different MAC addresses indicate a rogue access point mimicking a       legitimate network to intercept traffic (Evil Twin attack). Typhus Eye identifies these      anomalies instantly useful for basic wireless security audits.
  Standard duplicate SSIDs with the same MAC address (e.g. mesh routers) are correctly         ignored.
  
Libraries used:
  WiFi.h

How to use:
  1. Clone this repository
  2. Open typhus_eye.ino in Arduino IDE
  3. Select your ESP32 board
  4. Upload the sketch
  5. Open Serial Monitor at 115200 baud
  6. Typhus Eye will scan automatically every 10 seconds

Example output: 
_____________________________________________________________________________________________
  Typhus Eye searching...
```
1: Typhus_Victim_1   | -55 dBm | WPA2 (SAFE)      | Risiko: LOW    | MAC: AB:12:CD:34:EF:56
2: Typhus_Victim_2   | -63 dBm | OPEN (UNSAFE)     | Risiko: HIGH   | MAC: 11:22:33:44:55:66
3: Typhus_Victim_1   | -61 dBm | WPA2 (SAFE)       | Risiko: LOW    | MAC: FF:AA:BB:CC:DD:EE
4: Typhus_Victim_3   | -78 dBm | WPA3 (VERY SAFE)  | Risiko: VERY LOW | MAC: 00:1A:2B:3C:4D:5E

Typhus Eye checks for rogue APs...
    Possible Rogue AP detected: Typhus_Victim_1
```
--- Scan complete ---
_____________________________________________________________________________________________
Author: 
  Built as a personal learning project to share knowledge with others interested in wireless   networking and embedded security.

Disclaimer
  This tool is intended for educational purposes and authorized network analysis only.
  Do not use on networks you do not own or have explicit permission to scan.


