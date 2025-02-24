#include "pzem.h"
#include "Relays.h"
#include "LoraModule.h"
#include "nodeId.h"
#include "Buzz.h"

float temp, hum, nh3, h2s;
float humSum, tempSum, nh3Sum, h2sSum;
float humAvg, tempAvg, nh3Avg, h2sAvg;
String receivedData;
// Cập nhật thời gian chờ mặc định là 30 giây (30 * 1000 ms)

unsigned long previousMillis = 0;

void sendDataISR() {
    readAllSwitches();
    sendData(gatewayId, penCode, nodeId); //gửi dữ liệu controller
}

void setup() {
    SerialPzem_Setup(9600);
    DipSwitch_Setup();
    LoraSetup();
    initRelays();
    gatewayId = EEPROMLib::readString(0);
    waitDuration = 1000 * EEPROMLib::readInt(32);
    readAllSwitches();
}

void loop() {
    uint32_t currentMillis = millis();        // Lấy thời gian hiện tại

    if (currentMillis - previousMillis >= waitDuration) {
        previousMillis = currentMillis;       // Cập nhật thời điểm trước đó
        sendDataISR();                        // Gọi hàm gửi dữ liệu
    }

    if (receiveLoraData(receivedData)) {
        processReceivedData(receivedData);  // Xử lý dữ liệu nhận được
    }
    delay(50);
}
