#include "MQ136Module.h"

void MQ136_Setup(void){
    pinMode(PIN_MQ136,INPUT);
    pinMode(PIN_MQ136_POWER,OUTPUT);
    digitalWrite(PIN_MQ136_POWER,HIGH);
}

float readH2S(void){
    float adcValue = analogRead(PIN_MQ136);
    float h2s = 100.0 * (adcValue / 1023.0); // Chuyển đổi sang phần trăm
    return h2s;
}