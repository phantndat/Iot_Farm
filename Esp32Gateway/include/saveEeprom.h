#ifndef SAVEEEPROM_H
#define SAVEEEPROM_H

#include <Arduino.h>
#include <Preferences.h> 


void saveToEEPROM(const String& url);
String readFromEEPROM();
void clearEEPROM();  // Khai báo hàm xóa

#endif