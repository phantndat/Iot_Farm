#include "espCom.h"

int relayPins[16] = {PA0, PA1, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PB3, PB4, PB5, PB6, PB7};

HardwareSerial Serial3(PB11, PB10);

void SerialEsp_Setup(int baud){
      Serial3.begin(baud);
}


void initRelays() {
    for (int i = 0; i < 16; i++) {
        pinMode(relayPins[i], OUTPUT);
        digitalWrite(relayPins[i], LOW);  // Tắt hết các relay ban đầu
    }
}

// Hàm xử lý bật/tắt relay dựa trên số chân và trạng thái
void controlRelay(int pin, bool state) {
    digitalWrite(pin, state ? HIGH : LOW);
}
int k = 0;
void Esp_Receive(){
    if (Serial3.available()) {
        // Đọc dữ liệu JSON từ Serial3
        String jsonString = Serial3.readStringUntil('\n');
        jsonString.trim();

        JsonDocument doc; 

        DeserializationError error = deserializeJson(doc, jsonString);  

        if(jsonString == "AA") {
            Serial3.print(getPowerAverage());
        }
        else if(jsonString == "BB") {
            Serial3.print(power);
        }
        else if(error) {
        }
        else{
          relayControl(doc);
        }
        
    }
}

void relayControl(JsonDocument doc){
    // Lấy số Pin và trạng thái Value từ JSON
    int pin = doc["Pin"];  // Lấy giá trị của "Pin"
    int value = doc["Value"];  // Lấy giá trị của "Value"

    // Kiểm tra số Pin hợp lệ và điều khiển relay
    bool validPin = false;
    for (int i = 1; i < 17; i++) {
        if (i == pin) {
            int relayPin = relayPins[i-1];
            controlRelay(relayPin, value == 1);
            validPin = true;
            break;
        }
    }

    // Gửi phản hồi về trạng thái relay qua Serial3
    if (validPin) {
        Serial3.print(value);
    }
}


