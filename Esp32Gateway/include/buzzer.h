#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

void buzzer_Setup();
void buzzer_fail_Lora();
void buzzer_resetWiFi();
void buzzer_resetWiFi_Succes();
void buzzer_fail_mqtt();
void buzzer_wait_to_connect_wifi() ;
void cannot_get_time();
#endif // LIBRARY_H