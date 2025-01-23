#include "Wifi_Config.h"

WiFiManager wifiManager;

String resetState = "";

RTC_DATA_ATTR int shouldResetWiFi = 0;
int DelayTimeToReconnect = 5; // Thời gian giữa mỗi lần Reconnect WiFi (s)
int TimesReconnect = 12;      // Số lần kết nối

void setup_wifi()
{
  vTaskDelay(pdMS_TO_TICKS(10));
  WiFi.begin();
  int retryCount = 0;
  while (WiFi.status() != WL_CONNECTED && retryCount < 5)
  { // Thử lại tối đa 10 lần
    Serial.print("Connect to SSID: ");
    Serial.println(WiFi.SSID());
    buzzer_wait_to_connect_wifi();
    WiFi.reconnect(); // Thử kết nối lại với cấu hình WiFi đã lưu
    vTaskDelay(pdMS_TO_TICKS(2000));
    retryCount++;
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("");
    Serial.println("Reconnected to WiFi");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    buzzer_resetWiFi_Succes();
  }
  else
  {
    Serial.println("Failed to reconnect to WiFi");
    WiFi_Reset();
  }
}

void WiFi_Reset()
{
  buzzer_resetWiFi(); // trước khi reset wifi kêu 2 tiếng
  shouldResetWiFi = 1;
  Serial.println("Reset Starting...");
  wifiManager.setBreakAfterConfig(true);
  wifiManager.resetSettings();
  // Tạo cổng cài đặt WiFi thông qua WiFiManager
  if (!wifiManager.autoConnect("AmazingTech-IoT"))
  {
    Serial.println("failed to connect, we should reset as see if it connects");
    resetState = "Waiting...";
    delay(3000);
    ESP.restart();
    delay(5000);
  }
  buzzer_resetWiFi_Succes(); // reset thành công kêu dài 2 giây, kêu tiếp 2 tiếng
  Serial.println("Wifi Connected!");
  Serial.print("Địa chỉ IP: ");
  Serial.println(WiFi.localIP());
  resetState = "OK";
  shouldResetWiFi = 0;
}

void reconnectWiFi(void *)
{
  while (1)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("WiFi disconnected, attempting to reconnect...");

      int retryCount = 0;
      while (WiFi.status() != WL_CONNECTED && retryCount < TimesReconnect)
      {               // Thử lại tối đa 10 lần
        WiFi.begin(); // Thử kết nối lại với cấu hình WiFi đã lưu
        vTaskDelay(pdMS_TO_TICKS(DelayTimeToReconnect * 1000));
        buzzer_wait_to_connect_wifi();
        retryCount++;
      }

      if (WiFi.status() == WL_CONNECTED)
      {
        Serial.println("Reconnected to WiFi");
        buzzer_resetWiFi_Succes();
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
      }
      else
      {
        Serial.println("Failed to reconnect to WiFi");
        WiFi_Reset();
      }
    }
    vTaskDelay(pdMS_TO_TICKS(10000));
  }
}