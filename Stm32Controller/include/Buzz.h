#ifndef BUZZ_H  
#define BUZZ_H
#include <Arduino.h>

#define buzzerPin PB1
void failDHT(void);
void failLora(void);
void buzzer_Setup(void);
void changeTimeBuzzer(void);
void resetGatewayIDBuzz(void);
#endif 