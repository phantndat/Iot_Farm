#ifndef RELAYS_H
#define RELAYS_H

#include <ArduinoJson.h> 

extern int relayPins[16];

void initRelays(void);
void controlRelay(int pin, bool state);
void relayControl(JsonDocument doc);

#endif