#ifndef LORA_H
#define LORA_H

#include <Arduino.h>

void loraInit();
void loraSend(String data);
String loraReceive();

#endif
