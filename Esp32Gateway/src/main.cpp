#include <Arduino.h>
#include "Wifi_Config.h"
#include "Lora_Module.h"
#include "Stm32_Community.h"
#include "MQTT.h"
#include "getTime.h"
#include "buzzer.h"

String macAddress;
bool no_GatewayId = false;
void setup()
{
  Serial.begin(115200);
  buzzer_Setup();
  Serial.print("shouldResetWiFi: ");
  Serial.println(shouldResetWiFi);
  if (shouldResetWiFi == 0)
    setup_wifi();
  else
    WiFi_Reset();

  STM32_Setup(9600);
  

  macAddress = readFromEEPROM();
  if (macAddress.length() == 0)
  {
    macAddress = WiFi.macAddress();
    no_GatewayId = true;
  }
  
  Lora_Setup();
  MQTT_Setup();
  Serial.println("MacAddres: " + macAddress);

  getTime_Setup();

  xTaskCreate(MQTT_Process, "Task 1", 7000, NULL, 2, NULL);
  xTaskCreate(MQTT_Send_SensorValue, "Task 2", 7000, NULL, 2, NULL);
  xTaskCreate(getPowerPerMinute, "Task 3", 7000, NULL, 1, NULL);
  xTaskCreate(Lora_receive, "Task 4", 7000, NULL, 4, NULL);
  xTaskCreate(reconnectWiFi, "Task 5", 5000, NULL, 3, NULL);
}

void loop()
{
}
