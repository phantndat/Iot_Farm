#include "saveEeprom.h"

Preferences preferences;

void saveToEEPROM(const String &data)
{
  preferences.begin("storage", false); // Tên không gian lưu trữ, false là chế độ ghi
  preferences.putString("macAddress", data);
  preferences.end();
  Serial.println("Đã lưu URL vào EEPROM: " + data);
}

String readFromEEPROM()
{
  preferences.begin("storage", true); // Mở không gian lưu trữ ở chế độ chỉ đọc
  String data = preferences.getString("macAddress", "");
  preferences.end();
  Serial.println("Đọc URL từ EEPROM: " + data);
  return data;
}

void clearEEPROM()
{
  preferences.begin("storage", false); // Mở không gian lưu trữ ở chế độ ghi
  preferences.remove("macAddress");    // Xóa dữ liệu với key "macAddress"
  preferences.end();
  Serial.println("Đã xóa dữ liệu MAC Address khỏi EEPROM.");
}