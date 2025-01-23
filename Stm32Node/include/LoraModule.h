#ifndef LORAMODULE_H  
#define LORAMODULE_H
#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>
#include "Buzz.h"
#include "EEPROMLib.h"
#include <nodeId.h>
// Định nghĩa chân kết nối LoRa
#define SPI1_NSS  PA4
#define SPI1_SCK  PA5
#define SPI1_MISO PA6
#define SPI1_MOSI PA7  
#define SPI1_RESET PB0


extern String gatewayId;
extern int addrGatewayId;
extern uint32_t waitDuration;
void resetLoRaModule();
void LoraSetup(void);
void sendSensorData(String gatewayId, int penCode, int nodeId, float t, float h, float nh3, float h2s);
bool receiveLoraData(String &receivedData);  // Hàm mới để nhận dữ liệu
void processReceivedData(String &data); // Hàm mới để xử lý dữ liệu nhận được
void beginSend(void);
void endSend(void);
#endif 