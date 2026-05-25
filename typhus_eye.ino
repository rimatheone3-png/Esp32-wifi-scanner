#include <WiFi.h>

String getEncryption(wifi_auth_mode_t enc) {
  switch (enc) {
    case WIFI_AUTH_OPEN:        return "OPEN (UNSAFE)";
    case WIFI_AUTH_WPA_PSK:     return "WPA (OLD)";
    case WIFI_AUTH_WPA2_PSK:    return "WPA2 (SAFE)";
    case WIFI_AUTH_WPA_WPA2_PSK:return "WPA/WPA2";
    case WIFI_AUTH_WPA3_PSK:    return "WPA3 (VERY SAFE)";
    default:                    return "UNKNOWN";
  }
}

String getRiskLevel(wifi_auth_mode_t enc) {
  switch (enc) {
    case WIFI_AUTH_OPEN:     return "HIGH";
    case WIFI_AUTH_WPA_PSK:  return "MEDIUM";
    case WIFI_AUTH_WPA2_PSK: return "LOW";
    case WIFI_AUTH_WPA3_PSK: return "VERY LOW";
    default:                 return "UNKNOWN";
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Typhus Eye is open...");
}

void loop() {
  scanNetworks();
  delay(10000);
}

void scanNetworks() {
  Serial.println("\nTyphus Eye searching...");
  int n = WiFi.scanNetworks();

  if (n == 0) {
    Serial.println("Typhus Eye found no hosts");
    return;
  }

  // Ausgabe aller Netzwerke
  for (int i = 0; i < n; i++) {
    String ssid = WiFi.SSID(i);
    int rssi = WiFi.RSSI(i);
    wifi_auth_mode_t enc = WiFi.encryptionType(i);

    uint8_t* bssid = WiFi.BSSID(i);
    char bssidStr[18];
    sprintf(bssidStr, "%02X:%02X:%02X:%02X:%02X:%02X",
            bssid[0], bssid[1], bssid[2],
            bssid[3], bssid[4], bssid[5]);

    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(ssid);
    Serial.print(" | ");
    Serial.print(rssi);
    Serial.print(" dBm | ");
    Serial.print(getEncryption(enc));
    Serial.print(" | Risiko: ");
    Serial.print(getRiskLevel(enc));
    Serial.print(" | MAC: ");
    Serial.println(bssidStr);
  }

  // Rogue AP Check (läuft einmal, nach der Ausgabe)
  Serial.println("\nTyphus Eye checks for rogue APs...");
  bool foundRogue = false;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (WiFi.SSID(i) == WiFi.SSID(j)) {
        uint8_t* bssid1 = WiFi.BSSID(i);
        uint8_t* bssid2 = WiFi.BSSID(j);  // war vorher falsch: bssid statt bssid2

        bool same = true;
        for (int k = 0; k < 6; k++) {
          if (bssid1[k] != bssid2[k]) {
            same = false;
            break;
          }
        }

        if (!same) {
          Serial.print(" Possible Rogue AP detected: ");
          Serial.println(WiFi.SSID(i));
          foundRogue = true;
        }
      }
    }
  }

  if (!foundRogue) {
    Serial.println("No rogue APs detected.");
  }

  Serial.println("\n--- Scan complete ---");
}
