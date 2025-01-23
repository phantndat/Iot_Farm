#ifndef WIFICONFIG_H
#define WIFICONFIG_H

#include <WiFiManager.h>
#include "buzzer.h"
#include "saveEeprom.h"
extern int shouldResetWiFi;
extern WiFiManager wifiManager;
extern String resetState;

void setup_wifi();
void WiFi_Reset();
void reconnectWiFi(void *);
#endif // LIBRARY_H