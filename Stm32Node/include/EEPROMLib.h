#ifndef EEPROMLib_h
#define EEPROMLib_h

#include <Arduino.h>
#include <EEPROM.h>

class EEPROMLib
{
  public:
    // Hàm ghi chuỗi vào EEPROM
    static void writeString(int startAddress, const String &str);
    
    // Hàm đọc chuỗi từ EEPROM
    static String readString(int startAddress);
    
    static void writeInt(int startAddress, int value);
    
    // Hàm đọc int từ EEPROM
    static int readInt(int startAddress);
};

#endif