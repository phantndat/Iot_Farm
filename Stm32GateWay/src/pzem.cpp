#include "pzem.h"

HardwareSerial Serial2(PA3, PA2);  // Khai báo cổng Serial2 trên STM32 (PA2 là TX, PA3 là RX)
PZEM004Tv30 pzem(Serial2);  


int powerIndex;                     // Chỉ số để theo dõi vị trí trong mảng
double totalPower;            // Biến để lưu tổng giá trị công suất
bool esp32Get = false;
float power, powerTemp;
void SerialPzem_Setup(int baud) {
    Serial2.begin(baud);
    powerIndex = 0;                     // Chỉ số để theo dõi vị trí trong mảng
    totalPower = 0.0;     
}

void Pzem_Read(void) {
    if (!esp32Get) {
        powerTemp = pzem.power();
        if (isnan(powerTemp)) power = 0;
        else power = powerTemp;
        totalPower += power;
        powerIndex++;
    }
}

float getPowerAverage(void) {
    esp32Get = true;
    float averagePower = (powerIndex > 0) ? (totalPower / powerIndex) : 0.0;
    powerIndex = 0;
    totalPower = 0;
    esp32Get = false; // Reset trạng thái
    return averagePower;
}