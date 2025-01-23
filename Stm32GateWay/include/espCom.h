#ifndef ESPCOM_H
#define ESPCOM_H

#include <HardwareSerial.h>
#include <ArduinoJson.h> 
#include "pzem.h"
extern int relayPins[16];
extern bool esp32Get;

extern HardwareSerial Serial3;

void initRelays(void);
void controlRelay(int pin, bool state);
void SerialEsp_Setup(int baud);
void Esp_Receive(void);
void relayControl(JsonDocument doc);

#endif // LIBRARY_H