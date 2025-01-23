#include "lora.h"

#define PIN_M0 PA4
#define PIN_M1 PA5

HardwareSerial Serial2(PB11, PB10); // RX2 = PB11, TX2 = PB10

void loraInit() {
    pinMode(PIN_M0, OUTPUT);
    pinMode(PIN_M1, OUTPUT);
    digitalWrite(PIN_M0, HIGH);
    digitalWrite(PIN_M1, HIGH);
    delay(10);
    
    uint8_t config[] = {
        0xC0, // Lưu vào bộ nhớ
        0x12, // ADDH (Địa chỉ cao)
        0x34, // ADDL (Địa chỉ thấp)
        0x18, // SPED (UART 9600, không khí 2.4kbps, bật CRC)
        0x0F, // CH (Kênh 15, 433MHz)
        0xC3  // OPTION (Công suất 20dBm)
    };
    
    Serial2.write(config, sizeof(config));
    digitalWrite(PIN_M0, LOW);
    digitalWrite(PIN_M1, LOW);
    delay(10);


    Serial2.begin(9600);
}


void loraSend(String data) {
    Serial2.println(data);
}

String loraReceive() {
    String received = "";
    if (Serial2.available()) {
        received = Serial2.readString();
    }
    return received;
}
