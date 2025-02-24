#include "Relays.h"

int relayPins[16] = {PA0, PA1, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PB3, PB4, PB5, PB6, PB7};


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

