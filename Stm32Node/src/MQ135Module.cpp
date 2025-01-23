#include "MQ135Module.h"

void MQ135_Setup(void){
    pinMode(PIN_MQ135,INPUT);
    pinMode(PIN_MQ135_POWER,OUTPUT);
    digitalWrite(PIN_MQ135_POWER,HIGH);
}

float readNH3(void){
    float adcValue = analogRead(PIN_MQ135);
    float nh3 = 100.0 * (adcValue / 1023.0); // Chuyển đổi sang phần trăm
    return nh3;
}


