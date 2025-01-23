
#include "LoraModule.h"
#include "nodeId.h"
#include "dht11.h"
#include "MQ135Module.h"
#include "MQ136Module.h"
#include "Buzz.h"

float temp, hum, nh3, h2s;
float humSum, tempSum, nh3Sum, h2sSum;
float humAvg, tempAvg, nh3Avg, h2sAvg;
String receivedData;
// Cập nhật thời gian chờ mặc định là 30 giây (30 * 1000 ms)

unsigned long previousMillis = 0;

void sendDataISR() {
    // Chỉ cần sử dụng các biến đã khai báo toàn cục
    humSum = 0, tempSum = 0, nh3Sum = 0, h2sSum = 0;
    humAvg = 0, tempAvg = 0, nh3Avg = 0, h2sAvg = 0;

    turnOnDHT(true);
    delay(2000);  // Chờ để đảm bảo DHT11 ổn định
    for (int i = 0; i < 3; i++) {
        DHT11_Read(&temp, &hum);
        delay(5);  // Đọc DHT11
        nh3 = readNH3();
        delay(5);  // Đọc cảm biến NH3
        h2s = readH2S();
        delay(5);  // Đọc cảm biến H2S
        humSum += hum;
        tempSum += temp;
        nh3Sum += nh3;
        h2sSum += h2s;
        delay(1000);  // Chờ 2 giây giữa các lần đọc
    }
    humAvg = humSum / 3;
    tempAvg = tempSum / 3;
    nh3Avg = nh3Sum / 3;
    h2sAvg = h2sSum / 3;
    readAllSwitches();
    sendSensorData(gatewayId, penCode, nodeId, 33.3, 22.2, 11.1, 44.4);
    turnOnDHT(false);
    
}

void setup() {
    DipSwitch_Setup();
    DHT11_Setup();
    LoraSetup();
    MQ136_Setup();
    MQ135_Setup();
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
