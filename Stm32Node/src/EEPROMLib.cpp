#include "EEPROMLib.h"

void EEPROMLib::writeString(int startAddress, const String &str)
{
    // Chuyển String thành mảng char[]
    char charArray[str.length() + 1];
    str.toCharArray(charArray, sizeof(charArray));

    // Ghi từng ký tự vào EEPROM
    for (int i = 0; i < str.length() + 1; i++) {  // +1 để ghi ký tự kết thúc null '\0'
        EEPROM.write(startAddress + i, charArray[i]);
    }
}

String EEPROMLib::readString(int startAddress)
{
    String result = "";
    char ch;

    // Đọc dữ liệu từ EEPROM cho đến khi gặp '\0'
    for (int i = 0; i < EEPROM.length(); i++) {
        ch = EEPROM.read(startAddress + i);
        if (ch == '\0') {  // Dừng khi gặp ký tự kết thúc null
            break;
        }
        result += ch;
    }

    return result;
}

void EEPROMLib::writeInt(int startAddress, int value)
{
    byte* p = (byte*)(void*)&value;
    for (int i = 0; i < sizeof(value); i++) {
        EEPROM.write(startAddress + i, *(p + i));
    }
}

// Đọc int từ EEPROM
int EEPROMLib::readInt(int startAddress)
{
    int value = 0;
    byte* p = (byte*)(void*)&value;
    for (int i = 0; i < sizeof(value); i++) {
        *(p + i) = EEPROM.read(startAddress + i);
    }
    return value;
}

