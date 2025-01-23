#ifndef MQTT_H
#define MQTT_H

#include <WiFiClientSecure.h> //Test

#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "Lora_Module.h"
#include "Wifi_Config.h"
#include "Stm32_Community.h"
#include "buzzer.h"
#include "saveEeprom.h"

// extern WiFiClient espClient;  // Web
extern WiFiClientSecure espClient; // Test
extern PubSubClient client;

extern const char *mqtt_broker;
extern const int mqtt_port; // SSL port
extern const char *mqtt_username;
extern const char *mqtt_password;
extern String macAddress;
extern bool no_GatewayId;

struct SensorData
{
  float nh3;
  float h2s;
  float temp;
  float hum;
  int nodeId;
  int penCode;
  String GatewayId;
};

extern String receivedTopic;
extern String receivedPayload;
extern SensorData sensorData;

extern bool stateList[16];

void MQTT_Setup();
void publishMessage(const char *topic, const char *payload);
void processData(const String &data);
void callback(char *topic, byte *payload, unsigned int length);
void MQTT_Process(void *);
void MQTT_Send_SensorValue(void *);

extern const char *root_ca;

#endif // LIBRARY_H