#ifndef MQ136MODULE_H  
#define MQ136MODULE_H
#include <Arduino.h>

#define PIN_MQ136 PA2
#define PIN_MQ136_POWER PB4
float readH2S(void);
void MQ136_Setup(void);
#endif 