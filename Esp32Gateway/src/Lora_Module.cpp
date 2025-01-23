#include "Lora_Module.h"
std::vector<String> receivedDataList;
bool LoraSender = false;
void storeData(const String &data)
{
  receivedDataList.push_back(data);
}

void Lora_Setup()
{
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
  while (!LoRa.begin(433E6))
  {
    Serial.println("LoRa initialization failed!");
    // while (1);
    buzzer_fail_Lora();
  }
  // LoRa.setSpreadingFactor(12);   // SF cao
  // LoRa.setSignalBandwidth(62.5E3); // BW nhỏ
  // LoRa.setCodingRate4(8);       // CR cao
  Serial.println("LoRa initialized successfully!");
  LoRa.receive();
}

void Lora_receive(void *)
{
  while (1)
  {
    if (!LoraSender)
    {
      int packetSize = LoRa.parsePacket();
      if (packetSize)
      {
        String receivedData = "";
        while (LoRa.available())
        {
          receivedData += (char)LoRa.read(); // Read data
        }
        // Print received data
        Serial.print("Received LoRa data: ");
        Serial.println(receivedData);
        storeData(receivedData);
      }
      vTaskDelay(pdMS_TO_TICKS(50));
    }
    else
      vTaskDelay(pdMS_TO_TICKS(5000));
  }
}


void resetLoRaModule()
{
  pinMode(LORA_RST, OUTPUT);
  // Đặt chân RESET xuống mức LOW để reset module
  digitalWrite(LORA_RST, LOW);
  delay(10); // Giữ mức thấp trong 10ms
  // Đưa chân RESET trở lại mức HIGH
  digitalWrite(LORA_RST, HIGH);
  delay(10); // Chờ module khởi động lại
}
